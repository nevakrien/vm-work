# vm-work (currently under dev)
making a forth inspied VM for building a PL over

this VM has the goal of providing a "fast enough" interactive exprince on as many platforms as possible. we want to pander both to SIMD registers on desktop and to peripheral registers in embedded.

note that this VM assumes that the input code is correctly specified.
absolutly no safety gurnteas are provided by defualt and this includes some of Cs (or any compiled languge with an LLVM backend) sensabilties about Pointer Provenance

# IR vs Bytecode
because of the vast diffrence between targets it is impossible to make 1 build fits all.
diffrent chips simply have diffrent capabileties and thus on the lowest of levels would.

however for many reasons it is absolutly vital to expose an EXTERNAL IR that is consistent across all platforms. thus we need a compromise.

each instruction has 1 and only 1 true representation in the IR.
that representation can later be converted into a platform specific varient.

for instance on x64 the ADD(8,uint32) would be a unique internal opcode to allow for SIMD operations. however on Xtensa that is not needed and instead we would probably need a specilized "write perphiral" instruction. which would be nonsensical for most desktop chips.

aligment is yet another issue on this front i am not sure how to solve

# Instruction format (under dev)

### basic stack
```
push(type,n,alignment) //aligment here is assumed known stack aligment
pop(type,n,alignment)
```

### arithmetic
```
Add(type,type,n(runtime?),alignment)
Sub(type,type,n(runtime?),alignment)
Mul(type,type,n(runtime?),alignment)
Div(type,type,n(runtime?),alignment)
MulDiv(type,type,type,n(runtime?),alignment)
```

### vars handling
```
inject(type) //writes the top if the stack to a pointer below
unbox(type) //reads the top pointer

read-local(type,offset) //this is in relation to local frame

get-sp
set-sp

alloc-frame(size,alignment)
drop-frame
```

### control-flow
```
call
ret
jmp(offset)
jmpif(offset)

crash

call-c //calls a c function pointer with the signature void f(&vm);

iterupt-return
intrupt-set(code,func)
intrupt-unset(code)
```

note that intrupt handeling in an OS enviorment is translated as SIGNALS.
that makes interupt-return equivelent to return HOWEVER the IR should absolutly type error when a regular return is used.

### perphirals IO and such
```
read-IO(count(runtime?),stream)
write-IO(count(runtime?),stream)

open-IO //only for OS

read-reg(reg)  //only for embedded
write-reg(reg) //only for embedded
```

### threads?
this is potentially a future extension we will see

# types
Ptr T

u8 u16 u32 u64
i8 i16 i32 i64
r8 r16 r32 r64 (reals new format)
f16 f32 f64

# considerations
whether or not to include aligment is INCREDBLY tricky.
on the 1 hand adding that polution into every operation bloats the VM.
on the other hand not including it means even reading a 32bit int on 32bit is unaligned. we could hack around it by aligning the stack to a constant but that then removes the possibility of unaligned reads