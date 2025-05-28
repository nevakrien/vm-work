#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include "vm.h"

// TEST CODE
void test_push_pop_all_types() {
    char stack[64];
    Vm vm = { .sp = stack + sizeof(stack) };

    // Test 1: int32_t
    {
        int32_t val = 0x12345678;
        int32_t out = 0;
        push_value(&vm, &val, sizeof(val));
        pop_value(&vm, &out, sizeof(out));
        assert(out == 0x12345678);
    }

    // Test 2: int64_t
    {
        int64_t val = 0x1122334455667788;
        int64_t out = 0;
        push_value(&vm, &val, sizeof(val));
        pop_value(&vm, &out, sizeof(out));
        assert(out == 0x1122334455667788);
    }

    // Test 3: float
    {
        float val = 3.1415926f;
        float out = 0;
        push_value(&vm, &val, sizeof(val));
        pop_value(&vm, &out, sizeof(out));
        assert(out == val);
    }

    // Test 4: double
    {
        double val = 2.718281828;
        double out = 0;
        push_value(&vm, &val, sizeof(val));
        pop_value(&vm, &out, sizeof(out));
        assert(out == val);
    }

    // Test 5: uint8_t[4]
    {
        uint8_t val[4] = {1, 2, 3, 4};
        uint8_t out[4] = {0};
        push_value(&vm, val, sizeof(val));
        pop_value(&vm, out, sizeof(out));
        assert(memcmp(val, out, 4) == 0);
    }

    printf("All tests passed.\n");
}

int main() {
    test_push_pop_all_types();
    return 0;
}
