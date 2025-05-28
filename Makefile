GCC = gcc
CLANG = clang
CFLAGS = -Wall -Wextra -O3 -march=native

SRC = test.c
GCC_ASM = gcc.s
GCC_OBJ = gcc.o
GCC_BIN = gcc_test

CLANG_ASM = clang.s
CLANG_OBJ = clang.o
CLANG_BIN = clang_test

.PHONY: all clean

all: $(GCC_BIN) $(CLANG_BIN)

# GCC path
$(GCC_ASM): vm.c
	$(GCC) $(CFLAGS) -S vm.c -o $(GCC_ASM)

$(GCC_OBJ): $(GCC_ASM)
	$(GCC) -c $(GCC_ASM) -o $(GCC_OBJ)

$(GCC_BIN): $(SRC) $(GCC_OBJ)
	$(GCC) $(CFLAGS) $(SRC) $(GCC_OBJ) -o $(GCC_BIN)

# Clang path
$(CLANG_ASM): vm.c
	$(CLANG) $(CFLAGS) -S vm.c -o $(CLANG_ASM)

$(CLANG_OBJ): $(CLANG_ASM)
	$(CLANG) -c $(CLANG_ASM) -o $(CLANG_OBJ)

$(CLANG_BIN): $(SRC) $(CLANG_OBJ)
	$(CLANG) $(CFLAGS) $(SRC) $(CLANG_OBJ) -o $(CLANG_BIN)

clean:
	rm -f $(GCC_ASM) $(GCC_OBJ) $(GCC_BIN) \
	       $(CLANG_ASM) $(CLANG_OBJ) $(CLANG_BIN)
