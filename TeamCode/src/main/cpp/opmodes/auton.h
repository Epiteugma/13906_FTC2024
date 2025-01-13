#pragma once
#include "../lib/c_op_mode.h"
#include "../utils/kinematics/drivetrain.h"
#include "../utils/control/pid.h"
#include "../utils/odometry/odometry.h"
#include "../utils/utils.h"
#include "../utils/constants.h"
#include "../profiles/profiles.h"

class Auton : C_OpMode {
    using C_OpMode::C_OpMode;

    Odometry odometry{};
    Drivetrain drivetrain{};

    C_DcMotor *lift_1;
    C_DcMotor *lift_2;

    C_DcMotor *extend_motor;

    C_Servo *basket_servo;
    C_Servo *rotate_servo;

    double forward_power;
    double strafe_power;
    double turn_power;

    void printDebugInfo();
    void init();
public:
    void runOpMode() override;
};