#include "ivtentry.h"
#include <stdlib.h>
#include <dos.h>

IVTEntry* IVTEntry::ivt[256];

IVTEntry::IVTEntry(IVTNo num, PtrInterrupt new_intr) :
	ivt_number(num),
	my_event(NULL)
{
	old_interrupt = getvect(num);
	setvect(num, new_intr);
	ivt[num] = this;
}

IVTEntry::~IVTEntry() {
	setvect(ivt_number, old_interrupt);
}

void IVTEntry::signal() {
	if (!my_event) return; //ulaz je podesen ali nit ne ceka
	my_event->signal();
}

void IVTEntry::callOldIntr() {
	old_interrupt();
}

void IVTEntry::setEvent(IVTNo n, Event * ev) {
	if (ivt[n]->my_event) return;
	ivt[n]->my_event = ev;
}

void IVTEntry::removeEvent(IVTNo n, Event * ev) {
	if (ivt[n]->my_event != ev) return;
	ivt[n]->my_event = NULL;
}
