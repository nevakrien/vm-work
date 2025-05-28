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

note that the current implementation just ignores aligment all togther.
we can add it later but its just inherntly tricky

### arithmetic
```
Add(type,type,n(runtime?))
Sub(type,type,n(runtime?))
Mul(type,type,n(runtime?))
Div(type,type,n(runtime?))
MulDiv(type,type,type,n(runtime?))
```

### vars handling
```
inject(type,n(runtime?)) //writes the top if the stack to a pointer below
unbox(type) //reads the top pointer

read-local(type,offset) //this is in relation to local frame
write-local(type,offset) //this is in relation to local frame

get-sp
set-sp

alloc-frame(size)
drop-frame

write-const(16bit)
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

### register optimization
so a stack based VM if naively imlemented has a very hard time with basic arithmetic. to combat this we do want a small amount of regs but these should be ACTUAL hardware level regs.

in other words unlike a register machine where the number of hardware regs is artificially incresed we purposfully artificially decrese it.

we dont want to push this on the programer at all as this is an implementation detail and may be machine dependent. note that when replacing this backend with say LLVM this optimization would be done trivially by LLVM thus it is not needed in external APIs and would likelly just cause damage

small functions like ADD would have an inlined function definition that takes a register input and returns a register output.
this allows for chains off small arithmetic operations to be done entirly inside of a registers.

forth has the top of the stack optimization for this.
however it does not work for us since we actually dont look at the top of the stack as anything special

# types
Ptr T

u8 u16 u32 u64
i8 i16 i32 i64
r8 r16 r32 r64 (reals new format)
   f16 f32 f64

# considerations
whether or not to include aligment is INCREDBLY tricky.
on the 1 hand adding that polution into every operation bloats the VM.
on the other hand not including it puts us into some anoying machine dependnce (or unaligned reads for types like int) and missed SIMD optimizations.

we will do what C does and have the stack at natural aligment across frames. return values should generally match this aligment with padding