#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include "vm.h"

#define STACKSIZE 512 //has to be this minimum

// Basic push/pop round-trip tests
void test_push_pop_all_types(Vm* vm) {
    vm->sp = (char*)vm->sp + 64;

    // Test 1: int32_t
    {
        int32_t val = 0x12345678;
        int32_t out = 0;
        push_value(vm, &val, sizeof(val));
        pop_value(vm, &out, sizeof(out));
        assert(out == 0x12345678);
    }

    // Test 2: int64_t
    {
        int64_t val = 0x1122334455667788;
        int64_t out = 0;
        push_value(vm, &val, sizeof(val));
        pop_value(vm, &out, sizeof(out));
        assert(out == 0x1122334455667788);
    }

    // Test 3: float
    {
        float val = 3.1415926f;
        float out = 0;
        push_value(vm, &val, sizeof(val));
        pop_value(vm, &out, sizeof(out));
        assert(out == val);
    }

    // Test 4: double
    {
        double val = 2.718281828;
        double out = 0;
        push_value(vm, &val, sizeof(val));
        pop_value(vm, &out, sizeof(out));
        assert(out == val);
    }

    // Test 5: uint8_t[4]
    {
        uint8_t val[4] = {1, 2, 3, 4};
        uint8_t out[4] = {0};
        push_value(vm, val, sizeof(val));
        pop_value(vm, out, sizeof(out));
        assert(memcmp(val, out, 4) == 0);
    }

    printf("Basic push/pop tests passed.\n");
}

// Vector addition for uint32_t
void test_uint32_add(Vm* vm, Opcode op, int n) {
    vm->sp = (char*)vm->sp + 512;
    uint32_t a[16] = {0}, b[16] = {0}, out[16] = {0};

    for (int i = 0; i < n; i++) {
        a[i] = i;
        b[i] = i * 10;
    }

    push_value(vm, a, n * sizeof(uint32_t));
    push_value(vm, b, n * sizeof(uint32_t));
    vm_call(vm, op);
    pop_value(vm, out, n * sizeof(uint32_t));

    for (int i = 0; i < n; i++)
        assert(out[i] == a[i] + b[i]);
}

// Vector addition for _Float16
void test_float16_add(Vm* vm, Opcode op, int n) {
    vm->sp = (char*)vm->sp + 512;
    _Float16 a[16] = {0}, b[16] = {0}, out[16] = {0};

    for (int i = 0; i < n; i++) {
        a[i] = (_Float16)i;
        b[i] = (_Float16)(i * 0.25f);
    }

    push_value(vm, a, n * sizeof(_Float16));
    push_value(vm, b, n * sizeof(_Float16));
    vm_call(vm, op);
    pop_value(vm, out, n * sizeof(_Float16));

    for (int i = 0; i < n; i++) {
        _Float16 expected = a[i] + b[i];
        assert(out[i] == expected); // bitwise exact, _Float16 is deterministic
    }
}

int main() {
    char stack[STACKSIZE];
    Vm vm = { .sp = stack + sizeof(stack) };

    test_push_pop_all_types(&vm);

    test_uint32_add(&vm, UINT32_ADD,    1);
    test_uint32_add(&vm, UINT32_ADD2,   2);
    test_uint32_add(&vm, UINT32_ADD4,   4);
    test_uint32_add(&vm, UINT32_ADD8,   8);
    test_uint32_add(&vm, UINT32_ADD16, 16);

    test_float16_add(&vm, FLOAT16_ADD,    1);
    test_float16_add(&vm, FLOAT16_ADD2,   2);
    test_float16_add(&vm, FLOAT16_ADD4,   4);
    test_float16_add(&vm, FLOAT16_ADD8,   8);
    test_float16_add(&vm, FLOAT16_ADD16, 16);

    printf("All opcode tests passed.\n");
    return 0;
}
