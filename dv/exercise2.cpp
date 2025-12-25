#include <cstdint>
#include <catch2/catch_test_macros.hpp>
#include <VExercise2.h>

static void tick(VExercise2& m) {
    m.clk = 0; m.eval();
    m.clk = 1; m.eval();
}

TEST_CASE("Exercise2: Reasonable behavioral verification") {
    VExercise2 model;

    // Sample several initial states
    uint16_t seeds[] = {0x1, 0xACE1, 0x1234, 0xFFFF};

    for (uint16_t seed : seeds) {
        model.reset_n = 0;
        model.init = seed;
        tick(model);

        REQUIRE(model.out == seed);

        model.reset_n = 1;

        uint16_t prev = model.out;
        for (int i = 0; i < 100; ++i) {
            tick(model);

            uint16_t feedback =
                ((prev >> 15) ^ (prev >> 13) ^ (prev >> 12) ^ (prev >> 10)) & 1;

            uint16_t expected = (prev << 1) | feedback;
            REQUIRE(model.out == expected);

            prev = model.out;
        }
    }
}
