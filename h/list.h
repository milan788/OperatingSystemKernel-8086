#ifndef LIST_H_
#define LIST_H_
#include <stdlib.h>
#include "pcb.h"

typedef unsigned Time;
class PCB;

class List {
public:
	List() : head(NULL), tail(NULL), sum(0) {}
	void put(PCB* pcb, Time time);
	void backToScheduler();
	void backToSchedulerFirst();
	void decCounter();
private:
	struct Elem {
		PCB* pcb;
		volatile Time time;
		Elem* next;
		Elem(PCB* p, Time t, Elem* n = NULL) : pcb(p), time(t), next(n) {}
		~Elem() {}
	};
	Elem *head, *tail;
	Time sum;

	void insertAfter(Elem* temp, Elem* prev, Elem* novi);
};

#endif // !SLEEP_LIST_H_

