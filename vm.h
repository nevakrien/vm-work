typedef struct {
	char* sp;
} Vm;

void vm_call(Vm* vm,char opcode);

static inline void pop_value(Vm* vm,void* target,size_t count){
	memcpy(target,vm->sp,count);
	vm->sp+=count;
}

static inline void push_value(Vm* vm,void* target,size_t count){
	memcpy(vm->sp-count,target,count);
	vm->sp-=count;
}
