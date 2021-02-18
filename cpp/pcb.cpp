#include <stdlib.h>
#include <iostream.h>
#include <dos.h>
#include "SCHEDULE.H"
#include "pcb.h"
#include "thread.h"
#include "system.h"

const int PCB::NEW = 0, PCB::READY = 1, PCB::RUN = 2, PCB::END = 3, PCB::BLOCKED = 4;
volatile PCB* PCB::running = NULL;

PCB::PCB(StackSize stackSize, Time timeSlice, Thread* thr):
sp(0), ss(0), bp(0),
stack(NULL),
time_slice(timeSlice),
my_thread(thr),
state(NEW),
wtc_list(new List())
{
	if(stackSize > 65536) stack_size = 65536;
	else stack_size = stackSize;
	stack_size /= sizeof(StackSize);
}

PCB::~PCB() {
	delete stack;
	delete wtc_list;
}

void PCB::start() {
	if(state != NEW) return;
	alocStack();
	Scheduler::put((PCB*)this);
}

void PCB::alocStack() {
	stack = new unsigned[stack_size];
	stack[stack_size - 1] = 0x200;
	stack[stack_size - 2] = FP_SEG(wrapperRun);
	stack[stack_size - 3] = FP_OFF(wrapperRun);
	sp = FP_OFF(stack + stack_size - 12);
	bp = FP_OFF(stack + stack_size - 12);
	ss = FP_SEG(stack + stack_size - 12);
	state = READY;
}

void PCB::wrapperRun() {
	running->my_thread->run();
	lock;
	running->wtc_list->backToScheduler();
	running->state = END;
	unlock;
	dispatch();
}

void PCB::waitToComplete() {
	if(this == running || this->state == END || this->state == NEW) return;
	lock;
	running->state = BLOCKED;
	wtc_list->put((PCB*)running,0);
	unlock;
	dispatch();
}




