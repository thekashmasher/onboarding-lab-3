#include <cstdint>
#include <catch2/catch_test_macros.hpp>
#include <VExercise1.h>

static uint8_t ref(uint8_t op, uint8_t a, uint8_t b) {
    switch (op) {
        case 0: return a ^ b;
        case 1: return a << b;
        case 2: return b == 0 ? 0 : a % b;
        case 3: return ~(a & b);
        default: return 0;
    }
}

TEST_CASE("Exercise1: All operations, exhaustive") {
    VExercise1 model;

    for (uint8_t op = 0; op < 4; ++op) {
        model.op = op;
        for (uint16_t a = 0; a < 256; ++a) {
            for (uint16_t b = 0; b < 256; ++b) {
                model.a = a;
                model.b = b;
                model.eval();
                REQUIRE(model.out == ref(op, a, b));
            }
        }
    }
}
