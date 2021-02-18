#ifndef KERNEL_SEM_H_
#define KERNEL_SEM_H_
#include "semaphor.h"
#include "list.h"

class KernelSem {
private:
	friend class Semaphore;
	KernelSem(int init) : value(init), block_list(new List()) { id = sled_id++; }
	~KernelSem();

	int wait(int toBlock);
	void signal();
	int val() const;

	int value;
	List* block_list;
	int id;
	static int sled_id;
};

#endif // !KERNEL_SEM_H_

