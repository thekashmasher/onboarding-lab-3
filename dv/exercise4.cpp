#include <cstdint>
#include <catch2/catch_test_macros.hpp>
#include <VExercise4.h>

TEST_CASE("Exercise4: Decoder behavior") {
    VExercise4 model;

    model.alpha = 0xAA;
    model.beta  = 0x55;
    model.gamma = 0x0F;

    // cs = 0, sel is don't care
    model.cs = 0;
    for (int sel = 0; sel < 4; ++sel) {
        model.sel = sel;
        model.eval();
        REQUIRE(model.out == 0);
    }

    model.cs = 1;

    model.sel = 0; model.eval();
    REQUIRE(model.out == model.alpha);

    model.sel = 1; model.eval();
    REQUIRE(model.out == model.beta);

    model.sel = 2; model.eval();
    REQUIRE(model.out == model.gamma);

    model.sel = 3; model.eval();
    REQUIRE(model.out == (model.alpha & (model.beta | model.gamma)));
}
