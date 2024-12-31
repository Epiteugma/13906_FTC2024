#pragma once
#include "../lib/c_op_mode.h"
#include "../utils/utils.h"
#include "chrono"

class ServoTuner : C_OpMode {
    using C_OpMode::C_OpMode;

public:
    void runOpMode() override;
};