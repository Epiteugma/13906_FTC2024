#pragma once
#include <vector>
#include <robot.h>
#include <utils/utils.h>
#include <lib/c_op_mode.h>

class RegressorTest : C_OpMode {
    using C_OpMode::C_OpMode;
    Robot *robot;

public:
    void runOpMode() override;
};
