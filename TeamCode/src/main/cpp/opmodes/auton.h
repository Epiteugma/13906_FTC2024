#pragma once
#include "../lib/c_op_mode.h"
#include "../utils/kinematics/drivetrain.h"
#include "../utils/odometry/odometry.h"
#include "../utils/utils.h"
#include "../utils/constants.h"

class Auton : C_OpMode {
    using C_OpMode::C_OpMode;

    Odometry odometry{};
    Drivetrain drivetrain{};
    double forward_power = 0;

    void printDebugInfo();
public:
    void runOpMode() override;
};