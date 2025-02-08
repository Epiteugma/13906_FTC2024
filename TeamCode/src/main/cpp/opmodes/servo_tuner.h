#pragma once
#include <utils/utils.h>
#include <lib/c_op_mode.h>

class ServoTuner : C_OpMode {
    using C_OpMode::C_OpMode;
public:
    void runOpMode() override;
};