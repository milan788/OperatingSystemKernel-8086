#ifndef IVTENTRY_H_
#define IVTENTRY_H_
#include "event.h"
#include "krnlev.h"

typedef void interrupt (*PtrInterrupt)(...);
typedef unsigned char IVTNo;
class Event;

/*#define PREPAREENTRY(ivtNo,flag)\
void interrupt inter##ivtNo(...);\
IVTEntry entry##ivtNo(ivtNo, inter##ivtNo);\
void interrupt inter##ivtNo(...) {\
	entry##ivtNo.signal();\
	if(##flag)\
	entry##ivtNo.callOldIntr();\
}*/

class IVTEntry {
public:
	IVTEntry(IVTNo num, PtrInterrupt new_intr);
	~IVTEntry();
	void signal();
	void callOldIntr();
private:
	friend class KernelEv;
	static void setEvent(IVTNo n, Event* ev);
	static void removeEvent(IVTNo n, Event* ev);
	static IVTEntry* ivt[256];
	
	IVTNo ivt_number;
	Event* my_event;
	PtrInterrupt old_interrupt;
};
#endif // !IVTENTRY_H_

