#include "drivetrain.h"

void Drivetrain::drive(double forward_power, double turn_power) const {
    if (front_left != nullptr) front_left->setPower(forward_power + turn_power);
    if (front_right != nullptr) front_right->setPower(forward_power - turn_power);
    if (back_left != nullptr) back_left->setPower(forward_power + turn_power);
    if (back_right != nullptr) back_right->setPower(forward_power - turn_power);
}

void Drivetrain::drive(double forward_power, double strafe_power, double turn_power) const {
    if (front_left != nullptr) front_left->setPower(forward_power + turn_power + strafe_power);
    if (front_right != nullptr) front_right->setPower(forward_power - turn_power - strafe_power);
    if (back_left != nullptr) back_left->setPower(forward_power + turn_power - strafe_power);
    if (back_right != nullptr) back_right->setPower(forward_power - turn_power + strafe_power);
}