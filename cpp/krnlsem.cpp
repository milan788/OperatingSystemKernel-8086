#include "system.h"
#include "krnlsem.h"
#include <iostream.h>

int KernelSem::sled_id = 200;


KernelSem::~KernelSem() {
	block_list->backToScheduler();
	delete block_list;
}

int KernelSem::val() const {
	return value;
}

int KernelSem::wait(int toBlock) {
	if (toBlock) {
		value--;
		if (value >= 0) return 0;
		block_list->put((PCB*)PCB::running, 0);
		PCB::running->state = PCB::BLOCKED;
		//cout<<"Nit" << PCB::running->my_thread->id<<" se blokirala na semaforu"<< id <<endl;
		dispatch();
		return 1;
	}
	else {
		if (value > 0) { value--; return 0; }
		return -1;
	}
}

void KernelSem::signal() {
	value++;
	if (value <= 0){
		block_list->backToSchedulerFirst();
		//cout<<"Nit" << PCB::running->my_thread->id<<" se blokirala na semaforu"<< id <<endl;
	}
}
