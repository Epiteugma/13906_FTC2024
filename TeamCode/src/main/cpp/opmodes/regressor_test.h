#pragma once
#include "../lib/c_op_mode.h"
#include "../utils/kinematics/drivetrain.h"
#include "../utils/odometry/odometry.h"
#include "../utils/utils.h"
#include <chrono>
#include <cmath>
#include <map>
#include <vector>

class RegressorTest : C_OpMode {
public:
    using C_OpMode::C_OpMode;

    void runOpMode() override;
};