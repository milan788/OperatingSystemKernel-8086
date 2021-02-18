#include "thread.h"
#include "pcb.h"
#include "system.h"
#include <iostream.h>

int Thread::sled_id = 100;

Thread::Thread(StackSize stackSize, Time timeSlice) {
	lock;
	id = sled_id++;
	myPCB = new PCB(stackSize, timeSlice, this);
	unlock;
}

void Thread::start() {
	lock;
	myPCB->start();
	unlock;
}

Thread::~Thread() {
	waitToComplete();
	delete myPCB;
}


void Thread::waitToComplete() {
	myPCB->waitToComplete();
}

void Thread::sleep(Time timeToSleep) {
	System::systemSleep(timeToSleep);
}

void dispatch() {
	System::dispatch();
}

