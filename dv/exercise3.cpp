#include <cstdint>
#include <catch2/catch_test_macros.hpp>
#include <VExercise3.h>

static uint8_t mystery1_ref(uint8_t a, uint8_t b, uint8_t c) {
    switch (a & 0x3) {
        case 0: return (0b00 << 6) | ((b & 0x7) << 3) | (c & 0x7);
        case 1: return (0b01 << 6) | ((c & 0x7) << 3) | (b & 0x7);
        case 2: return b;
        case 3: return c;
    }
    return 0;
}

static uint16_t mystery2_ref(
    uint16_t prev,
    uint8_t a_in,
    uint8_t b_in,
    int state
) {
    switch (state) {
        case 0: return (a_in << 8) | (prev & 0xFF);
        case 1: return (prev & 0xFF00) | b_in;
        case 2: return ((prev & 0xFF) << 8) | (prev >> 8);
        case 3:
            return ((prev & 0x000F) << 12) |
                   ((prev & 0x00F0) << 4)  |
                   ((prev & 0x0F00) >> 4)  |
                   ((prev & 0xF000) >> 12);
        case 4: return __builtin_parity(prev);
    }
    return 0;
}

TEST_CASE("Exercise3: Integrated behavior") {
    VExercise3 model;

    model.clk = 1;
    model.reset = 1;
    model.a_in = 0x12;
    model.b_in = 0x34;
    model.a = 1;
    model.b = 0x56;
    model.c = 0x78;

    model.eval();
    model.clk = 0;
    model.eval();

    uint16_t expected =
        (model.b_in << 8) | model.a_in;
    REQUIRE(model.out == expected);

    model.reset = 0;

    uint16_t prev = model.out;
    for (int state = 0; state < 5; ++state) {
        model.clk = 1; model.eval();
        model.clk = 0; model.eval();

        uint8_t d = mystery1_ref(model.a, model.b, model.c);
        uint16_t ref = mystery2_ref(prev, d, d, state);

        REQUIRE(model.out == ref);
        prev = model.out;
    }
}
