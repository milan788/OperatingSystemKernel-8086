#include "system.h"
#include <stdlib.h>
#include <iostream.h>
#include <dos.h>
#include "thread.h"
#include "pcb.h"
#include "SCHEDULE.H"

//static polja klase System
volatile Time 	System::time_left = defaultTimeSlice;
volatile int 	System::disp = 0;
volatile int 	System::lock_flag = 0;
PtrInterrupt 	System::old_timer = NULL;
PCB* 			System::main_thread = NULL;
IdleThread*		System::idle_thread = NULL;
List* 			System::sleep_list = NULL;

void System::inic() {
	asm cli
	PCB::running = (volatile PCB*) new PCB(0, defaultTimeSlice, NULL);
	main_thread = (PCB*)PCB::running;
	PCB::running->stack = NULL;
	PCB::running->state = PCB::RUN;

	//napraviti idle thread
	idle_thread = new IdleThread();
	idle_thread->start();
	Scheduler::get(); //proveriti

	//pravljenje sleep liste
	sleep_list = new List();

	//podesavanje timer prekidne rutine
	old_timer = getvect(0x08);
	setvect(0x08, timer);
	setvect(0x60, old_timer);
	asm sti
}

void System::restore() {
	asm cli
	//vracanje stare timer prekidne rutine
	setvect(0x08, old_timer);

	//brisanje liste
	delete sleep_list;

	//brisanje idle niti
	idle_thread->myPCB->state = PCB::END;
	delete idle_thread;
	idle_thread = NULL;

	//brisanje main niti
	main_thread->state = PCB::END;
	delete main_thread;
	main_thread = NULL;
	asm sti
}

void System::dispatch() {
	asm cli
	disp = 1;
	timer();
	asm sti
}

extern void tick();

void interrupt System::timer(...) {
	static volatile unsigned int tsp, tss, tbp;
	if(!disp) {
		asm int 60h;
		tick();
		sleep_list->decCounter();
		sleep_list->backToScheduler();
	}

	if (!disp && PCB::running->time_slice != 0) time_left--;
	if ((time_left == 0 && PCB::running->time_slice != 0) || disp) {
		if(lock_flag == 0) {
			disp = 0;
			asm {
				mov tsp, sp
				mov tss, ss
				mov tbp, bp
			}

			PCB::running->sp = tsp;
			PCB::running->ss = tss;
			PCB::running->bp = tbp;

			if(PCB::running->state == PCB::RUN && PCB::running != idle_thread->myPCB) {
				PCB::running->state = PCB::READY;
				Scheduler::put((PCB*)PCB::running);
			}
			PCB::running = Scheduler::get();
			if(PCB::running == NULL) { PCB::running = idle_thread->myPCB; }
			PCB::running->state = PCB::RUN;

			tsp = PCB::running->sp;
			tss = PCB::running->ss;
			tbp = PCB::running->bp;

			time_left = PCB::running->time_slice;
			asm {
				mov sp, tsp
				mov ss, tss
				mov bp, tbp
			}
		} else disp = 1;
	}
}

void System::systemLock() {
	lock_flag++;
}

void System::systemUnlock() {
	if(--lock_flag == 0 && disp == 1) dispatch();
}

void System::systemSleep(Time timeToSleep) {
	if(timeToSleep > 0) {
		lock;
		sleep_list->put((PCB*)PCB::running,timeToSleep);
		PCB::running->state = PCB::BLOCKED;
		unlock;
	}
	dispatch();
}



