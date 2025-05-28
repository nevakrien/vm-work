#include "stdint.h"
#include "string.h"

typedef struct {
	char* sp;
} Vm;

static inline void pop_value(Vm* vm,void* target,size_t count){
	memcpy(vm->sp+1-count,target,count);
	vm->sp-=count;
}

static inline void push_value(Vm* vm,void* target,size_t count){
	memcpy(target,vm->sp+1-count,count);
	vm->sp+=count;
}

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
			ADD_N_TS(uint32_t,1);
			break;
		case 1:
			ADD_N_TS(uint32_t,2);
			break;
		case 2:
			ADD_N_TS(uint32_t,4);
			break;
		case 3:
			ADD_N_TS(uint32_t,8);
			break;
		case 4:
			ADD_N_TS(uint32_t,16);
			break;
	}
}