#ifndef VM_H
#define VM_H

typedef struct {
	char* sp;
} Vm;

typedef enum {
	UINT32_ADD=0,
	UINT32_ADD2,
	UINT32_ADD4,
	UINT32_ADD8,
	UINT32_ADD16,

	FLOAT16_ADD=8,
	FLOAT16_ADD2,
	FLOAT16_ADD4,
	FLOAT16_ADD8,
	FLOAT16_ADD16,
} Opcode;


void vm_call(Vm* vm,Opcode opcode);

static inline void pop_value(Vm* vm,void* target,size_t count){
	memcpy(target,vm->sp,count);
	vm->sp+=count;
}

static inline void push_value(Vm* vm,void* target,size_t count){
	memcpy(vm->sp-count,target,count);
	vm->sp-=count;
}

#endif //VM_H