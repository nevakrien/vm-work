# vm-work
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

# Instruction format (under dev)

### arithmetic
```
Add(type,type,n)
Sub(type,type,n)
Mul(type,type,n)
Div(type,type,n)
MulDiv(type,type,type,n)
```

### vars handling
```
inject(type) //writes the top if the stack to a pointer below
unbox(type) //reads the top pointer

read-local(type,offset) //this is in relation to local frame

get-sp
set-sp

alloc-frame(size,aligment)
drop-frame(stack-ptr)

```

### control-flow
```
call
jmp
jmpif
ret

crash

call-c //calls a c function pointer with the signature void f(&vm);

iterupt-return
intrup-set(code,func)
intrup-unset(code)
```

note that intrupt handeling in an OS enviorment is translated as SIGNALS.
that makes interupt-return equivelent to return HOWEVER the IR should absolutly type error when a regular return is used.

### perphirals IO and such
```
read-IO(count,stream)
write-IO(count,stream)

open-IO(c-string) //only for OS

read-reg(reg)  //only for embedded
write-reg(reg) //only for embedded
```

### threads?
this is potentially a future extension we will see