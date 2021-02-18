#include "system.h"
#include "SCHEDULE.H"
#include "krnlev.h"
#include "ivtentry.h"
#include <iostream.h>

KernelEv::KernelEv(IVTNo ivtNo, Event* ev) : 
	my_event(ev), 
	my_thread(PCB::running),
	entry(ivtNo), 
	value(1) 
{
	IVTEntry::setEvent(ivtNo, this->my_event); //sta ako je ulaz vec zauzet?
}

KernelEv::~KernelEv() {
	//if (value = 0) signal(); moze da se desi ako neka druga nit unistava objekat a nije my_thread, 
	//mada ne bi trebalo da se desi uopste
	IVTEntry::removeEvent(entry, this->my_event); 
}

void KernelEv::wait() {
	lock;
	if (!value) { unlock; return; }
	if (PCB::running != my_thread) { unlock; return; }
	PCB::running->state = PCB::BLOCKED;
	//cout<<"Nit se blokirala na dogadjaju" <<endl;
	value = 0;
	unlock;
	dispatch();
}

void KernelEv::signal() {
	lock;
	if (value) { unlock; return; }
	Scheduler::put((PCB*)my_thread);
	//cout<<"Nit se odblokirala na dogadjaju" <<endl;
	value = 1;
	unlock;
	dispatch();
}
