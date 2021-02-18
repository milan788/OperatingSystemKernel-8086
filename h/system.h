#ifndef SYSTEM_H
#define SYSTEM_H
#include "thread.h"
#include "idle.h"
#include "list.h"

typedef void interrupt (*PtrInterrupt)(...);

//makroi
#define lock 	System::systemLock()
#define unlock 	System::systemUnlock()

class System {
public:
	static void inic();
	static void restore();
	static void dispatch();

	static void systemLock();
	static void systemUnlock();
	static void systemSleep(Time timeToSleep);
private:
	System();
	static void interrupt 	timer(...);
	static volatile int		disp;
	static volatile Time 	time_left;
	static PtrInterrupt 	old_timer;

	static IdleThread* 	idle_thread;
	static PCB* 		main_thread;
	static List* 		sleep_list;
	static volatile int lock_flag;
};

#endif
