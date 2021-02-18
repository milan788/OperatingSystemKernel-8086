#ifndef _event_h_
#define _event_h_
#include "krnlev.h"
#include "ivtentry.h"
#include "prpren.h"

typedef unsigned char IVTNo;
class KernelEv;
class IVTEntry;

class Event {
public:
	Event(IVTNo ivtNo);
	~Event();
	void wait();
protected:
	friend class KernelEv;
	friend class IVTEntry;
	void signal(); // can call KernelEv
private:
	KernelEv * myImpl;
};

#endif
