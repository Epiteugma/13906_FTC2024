#include "../lib/hardware/c_dc_motor.h"

struct Drivetrain {
    C_DcMotor *front_left;
    C_DcMotor *front_right;
    C_DcMotor *back_left;
    C_DcMotor *back_right;

    void drive(double forward_power, double turn_power) const;
    void drive(double forward_power, double strafe_power, double turn_power) const;
};