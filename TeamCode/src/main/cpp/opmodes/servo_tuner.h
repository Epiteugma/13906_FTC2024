#pragma once
#include "../lib/c_op_mode.h"

class ServoTuner : C_OpMode {
public:
    using C_OpMode::C_OpMode;

    void runOpMode() override;
};