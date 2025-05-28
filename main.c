#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "vm.h"

void test_opcode(char opcode, int count) {
    char stack[4096] = {0};
    Vm vm = { .sp = stack + sizeof(stack) };

    _Float16 one = (_Float16)1.0;
    _Float16 two = (_Float16)2.0;
    _Float16 expected = (_Float16)3.0;

    // Push inputs: first `count` x 1.0, then `count` x 2.0
    for (int i = 0; i < count; i++)
        push_value(&vm, &one, sizeof(_Float16));
    for (int i = 0; i < count; i++)
        push_value(&vm, &two, sizeof(_Float16));

    vm_call(&vm, opcode);

    // Pop and assert all values == 3.0
    for (int i = 0; i < count; i++) {
        _Float16 result;
        pop_value(&vm, &result, sizeof(_Float16));
        assert(expected==result);
    }

    printf("opcode %d passed\n", opcode);
}

int main(void) {
    test_opcode(0, 1);
    test_opcode(1, 2);
    test_opcode(2, 4);
    test_opcode(3, 8);
    test_opcode(4, 16);
    printf("All tests passed.\n");
    return 0;
}
