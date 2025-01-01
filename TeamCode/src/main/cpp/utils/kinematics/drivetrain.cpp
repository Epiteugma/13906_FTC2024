#include "drivetrain.h"

void Drivetrain::drive(double forward_power, double turn_power) const {
    if (front_left != nullptr) front_left->setPower((forward_power + turn_power) * this->multiplier);
    if (front_right != nullptr) front_right->setPower((forward_power - turn_power) * this->multiplier);
    if (back_left != nullptr) back_left->setPower((forward_power + turn_power) * this->multiplier);
    if (back_right != nullptr) back_right->setPower((forward_power - turn_power) * this->multiplier);
}

void Drivetrain::drive(double forward_power, double strafe_power, double turn_power) const {
    double magnitude = std::hypot(forward_power, strafe_power);
    double direction = std::atan2(forward_power, strafe_power);

    math::vec2 v{
        magnitude > 1.0 ? 1.0 : magnitude,
        0.0
    };

    v.rotate(direction);

    if (front_left != nullptr) front_left->setPower((v.y + v.x + turn_power) * this->multiplier);
    if (front_right != nullptr) front_right->setPower((v.y - v.x - turn_power) * this->multiplier);
    if (back_left != nullptr) back_left->setPower((v.y - v.x + turn_power) * this->multiplier);
    if (back_right != nullptr) back_right->setPower((v.y + v.x - turn_power) * this->multiplier);
}