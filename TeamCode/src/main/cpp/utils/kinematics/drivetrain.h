#pragma once
#include <cmath>
#include <lib/hardware/c_dc_motor.h>
#include <utils/maths.h>

class Drivetrain {
public:
    double multiplier = 1.0;

    C_DcMotor *front_left;
    C_DcMotor *front_right;
    C_DcMotor *back_left;
    C_DcMotor *back_right;

    Drivetrain(C_DcMotor *front_left, C_DcMotor *front_right, C_DcMotor *back_left, C_DcMotor *back_right);
    void drive(maths::vec3 power);
};