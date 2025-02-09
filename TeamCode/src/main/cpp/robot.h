#pragma once
#include <constants.h>
#include <lib/c_op_mode.h>
#include <utils/kinematics/drivetrain.h>
#include <utils/odometry/odometry.h>

class Robot {
public:
    Drivetrain *drivetrain;
    Odometry *odometry;

    C_DcMotor *lift_1;
    C_DcMotor *lift_2;

    C_DcMotor *extend_motor;

    C_Servo *rotate_servo;
    C_Servo *pickup_servo;
    C_Servo *basket_servo;

    Robot(C_OpMode *op_mode);
};