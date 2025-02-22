#pragma once
#include <robot.h>
#include <lib/c_op_mode.h>
#include <utils/utils.h>
#include <utils/control/pid.h>
#include <utils/control/trapezoidal_feedforward.h>

class FeedForwardTest : C_OpMode {
    using C_OpMode::C_OpMode;

    TrapezoidalFeedforward *ff;
    Robot *robot;
public:
    void runOpMode() override;
};