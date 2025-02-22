#pragma once
#include <robot.h>
#include <lib/c_op_mode.h>
#include <utils/utils.h>
#include <utils/control/pid.h>

class FeedForwardTest : C_OpMode {
    using C_OpMode::C_OpMode;

    const double kS = 0.085317;
    const double kV = 0.489367;
    const double max_velocity = (1.0 - this->kS) / this->kV;
    const double time_to_max_velocity = 1.0;

    Robot *robot;
public:
    void runOpMode() override;
};