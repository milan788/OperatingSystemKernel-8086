#ifndef THREAD_H_
#define THREAD_H_
#include "pcb.h"

typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096;

typedef unsigned int Time; // time, x 55ms
const Time defaultTimeSlice = 2; // default = 2*55ms

//typedef int ID;

//class PCB; // Kernel's implementation of a user's thread

class Thread {
public:
	void start();
	virtual ~Thread();
	void waitToComplete();
	static void sleep(Time timeToSleep);
protected:
	friend class PCB;
	friend class System;
	Thread (StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);
	virtual void run() = 0;
private:
	PCB* myPCB;
	int id;
	static int sled_id;
};

void dispatch ();

#endif /* THREAD_H_ */
