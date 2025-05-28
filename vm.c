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

void vm_call(Vm* vm,Opcode opcode){
	switch (opcode){
		case UINT32_ADD:
			ADD_N_TS(uint32_t,1);
			break;
		case UINT32_ADD2:
			ADD_N_TS(uint32_t,2);
			break;
		case UINT32_ADD4:
			ADD_N_TS(uint32_t,4);
			break;
		case UINT32_ADD8:
			ADD_N_TS(uint32_t,8);
			break;
		case UINT32_ADD16:
			ADD_N_TS(uint32_t,16);
			break;

		case FLOAT16_ADD:
			ADD_N_TS(_Float16,1);
			break;
		case FLOAT16_ADD2:
			ADD_N_TS(_Float16,2);
			break;
		case FLOAT16_ADD4:
			ADD_N_TS(_Float16,4);
			break;
		case FLOAT16_ADD8:
			ADD_N_TS(_Float16,8);
			break;
		case FLOAT16_ADD16:
			ADD_N_TS(_Float16,16);
			break;
	}
}