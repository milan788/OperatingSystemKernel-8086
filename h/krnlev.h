#ifndef KERNEL_EVENT_H_
#define KERNEL_EVENT_H_
#include "event.h"

/*
semafor sme da ima max vrednost 1 - samo jedna nit moze da ceka na ulazu.
za wait - samo nit koja je napravila obj moze na njemu da se blokira - polje my_thread

*/
class PCB;

typedef unsigned char IVTNo;

class KernelEv {
private:
	friend class Event;
	KernelEv(IVTNo ivtNo, Event* ev);
	~KernelEv();
	void wait();
	void signal();
	
	Event* my_event;
	volatile PCB* my_thread;
	IVTNo entry;
	unsigned value;
	//int blocked; mozda treba
};

#endif // !KERNEL_EVENT_H_

