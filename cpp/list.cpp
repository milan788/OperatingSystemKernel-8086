#include <iostream.h>
#include "list.h"
#include "SCHEDULE.H"

void List::put(PCB* pcb, Time time) {
	Elem* novi = new Elem(pcb, time);
	if (time >= sum) {
		time -= sum; sum += time;
		novi->time = time;
		if (!head) head = novi;
		else tail->next = novi;
		tail = novi;
	}
	else {
		Elem *prev = new Elem(NULL, 0, head), *temp = prev, //pomocni element na pocetku sa vremenom 0
		*curr = head;

		//vreme na koje ceka nit na koju pokazuje curr (stvarno vreme),
		//posto je time stvarno vreme za novu nit
		Time curr_time = curr->time;

		//treba da bude sortirano po stvarnim vremenima
		while (curr && time >= curr_time) {
			novi->time -= prev->time;
			prev = curr; curr = curr->next;
			curr_time += curr->time;
		}
		novi->time -= prev->time;
		curr->time -= novi->time;
		insertAfter(temp, prev, novi);
		delete temp;
	}
}

void List::insertAfter(Elem* temp, Elem* prev, Elem* novi) {
	if (prev == temp) {
		novi->next = head;
		head = novi;
	}
	else {
		Elem* next = prev->next;
		prev->next = novi;
		novi->next = next;
	}
}

void List::backToScheduler() {
	if (head && head->time != 0) return;
	while (head && head->time == 0) {
		Elem* temp = head;
		Scheduler::put(temp->pcb);
		delete temp;
		head = head->next;
	}
	if(!head) tail = head;
}

void List::backToSchedulerFirst() {
	if(!head) return;
	Elem* temp = head;
	head = head->next;
	Scheduler::put(temp->pcb);
	delete temp;
}

void List::decCounter() {
	if (!head || (head && head->time == 0)) return;
	head->time--;
	sum--;
}

/*void List::print() { //izbrisati
	Elem* temp = head;
	while (temp) {
		cout << "[" << temp->time << "]-> ";
		temp = temp->next;
	} cout << endl;
}*/
