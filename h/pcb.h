#ifndef PCB_H_
#define PCB_H_
#include "thread.h"
#include "list.h"

typedef unsigned long StackSize;
typedef unsigned int Time; // time, x 55ms
class Thread;
class List;

class PCB {
public:
	static const int NEW, READY, RUN, END, BLOCKED;
private:
	friend class System;
	friend class Thread;
	friend class KernelSem;
	friend class KernelEv;
	PCB(StackSize stackSize, Time timeSlice, Thread* thr);
	~PCB();
	void start();
	void waitToComplete();
	unsigned sp;
	unsigned ss;
	unsigned bp;

	unsigned* stack;
	StackSize stack_size;
	void alocStack();

	Time time_slice;

	Thread* my_thread;
	volatile int state;

	static volatile PCB* running;
	static void wrapperRun();
	List* wtc_list;
};

#endif /* PCB_H_ */
