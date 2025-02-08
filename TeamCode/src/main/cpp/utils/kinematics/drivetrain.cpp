#include "drivetrain.h"

Drivetrain::Drivetrain(C_DcMotor *front_left, C_DcMotor *front_right, C_DcMotor *back_left, C_DcMotor *back_right) {
    this->front_left = front_left;
    this->front_right = front_right;
    this->back_left = back_left;
    this->back_right = back_right;
}

void Drivetrain::drive(maths::vec3 power) {
    double direction = std::atan2(power[0], power[2]);
    double magnitude = std::hypot(power[0], power[2]);

    magnitude -= std::abs(power[1]);
    magnitude *= this->multiplier;

    maths::vec3 motor_powers{
        std::cos(direction) * magnitude - std::sin(direction) * magnitude, // (strafe) left + right
        power[1] * this->multiplier, // (turn) left + right
        std::sin(direction) * magnitude + std::cos(direction) * magnitude, // forward + back
    };

    if (this->front_left) this->front_left->setPower   (motor_powers[2] + motor_powers[1] + motor_powers[0]);
    if (this->front_right) this->front_right->setPower (motor_powers[2] - motor_powers[1] - motor_powers[0]);
    if (this->back_left) this->back_left->setPower     (motor_powers[2] + motor_powers[1] - motor_powers[0]);
    if (this->back_right) this->back_right->setPower   (motor_powers[2] - motor_powers[1] + motor_powers[0]);
}