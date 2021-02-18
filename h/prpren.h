#ifndef PRPREN_H_
#define PRPREN_H_

#define PREPAREENTRY(ivtNo,flag)\
void interrupt inter##ivtNo(...);\
IVTEntry entry##ivtNo(ivtNo, inter##ivtNo);\
void interrupt inter##ivtNo(...) {\
	entry##ivtNo.signal();\
	if(##flag)\
	entry##ivtNo.callOldIntr();\
}

#endif /* PRPREN_H_ */
