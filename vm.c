#include "stdint.h"
#include "string.h"
#include "vm.h"

#define ADD_N_TS(t,n) \
	do{\
		t a[n],b[n];\
			pop_value(vm,&b,sizeof(a));\
			pop_value(vm,&a,sizeof(b));\
\
			for(int i=0;i<n;i++)\
				a[i]+=b[i];\
\
			push_value(vm,&a,sizeof(a));\
	}while(0)\

void vm_call(Vm* vm,char opcode){
	switch (opcode){
		case 0:
			ADD_N_TS(_Float16,1);
			break;
		case 1:
			ADD_N_TS(_Float16,2);
			break;
		case 2:
			ADD_N_TS(_Float16,4);
			break;
		case 3:
			ADD_N_TS(_Float16,8);
			break;
		case 4:
			ADD_N_TS(_Float16,16);
			break;
	}
}