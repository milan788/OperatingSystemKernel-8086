#include "system.h"
#include "semaphor.h"

Semaphore::Semaphore(int init) {
	lock;
	myImpl = new KernelSem(init);
	unlock;
}

Semaphore::~Semaphore() {
	lock;
	delete myImpl;
	unlock;
}

int Semaphore::wait(int toBlock) {
	lock;
	int ret = myImpl->wait(toBlock);
	unlock;
	return ret;
}

void Semaphore::signal() {
	lock;
	myImpl->signal();
	unlock;
}

int Semaphore::val() const {
	lock;
	int ret = myImpl->val();
	unlock;
	return ret;
}
