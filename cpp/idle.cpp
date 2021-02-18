#include <iostream.h>
#include "idle.h"
#include "system.h"

void IdleThread::run() {
	while(cnt++ > 0) {
		if(cnt == 100) cnt = 1;
		//lock; cout<< "~~~~~~~~~idle~~~~~~~~~~~~" << endl; unlock;
		for(int m = 0; m < 4000; m++)
			for(long n = 0; n < 30000; n++);
	}
}
