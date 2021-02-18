#ifndef IDLE_H_
#define IDLE_H_
#include "thread.h"

class IdleThread: public Thread {
protected:
	friend class System;
	IdleThread() : Thread(), cnt(1) {}
	void run();
	volatile int cnt;
};



#endif /* IDLE_H_ */
