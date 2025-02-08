#include "odometry.h"

void Odometry::update() {
    auto now = high_resolution_clock::now();

    int delta_left = this->left->getCurrentPosition() - this->last_left;
    int delta_right = this->right->getCurrentPosition() - this->last_right;
    int delta_perp = this->perp == nullptr ? 0 : this->perp->getCurrentPosition() - this->last_perp;
    duration<double> delta_time = now - this->last_update;

    this->last_left += delta_left;
    this->last_right += delta_right;
    this->last_perp += delta_perp;
    this->last_update = now;

    double phi = (delta_right - delta_left) / this->track_width;

    //math::vec2 robot_relative = {
    //    std::sin(this->theta + delta_time.count() * phi) - std::sin(this->theta),
    //    -std::cos(this->theta + delta_time.count() * phi) + std::cos(this->theta)
    //};

    math::vec2 robot_relative{
        delta_perp + (phi * this->perp_offset),
        (delta_right + delta_left) / 2.0,
    };

    double phi_integrator[] = {
        std::sin(phi) / phi, (std::cos(phi) - 1) / phi,
        (-std::cos(phi) + 1) / phi, std::sin(phi) / phi
    };

    if (phi == 0.0) {
        phi_integrator[0] = 1.0;
        phi_integrator[1] = 0.0;
        phi_integrator[2] = 0.0;
        phi_integrator[3] = 1.0;
    }

    math::vec2 field_relative{
        phi_integrator[0] * robot_relative.x + phi_integrator[1] * robot_relative.y,
        phi_integrator[2] * robot_relative.x + phi_integrator[3] * robot_relative.y,
    };

    field_relative.rotate(this->theta);

    this->velocity.x = field_relative.x / delta_time.count();
    this->velocity.y = field_relative.y / delta_time.count();

    this->pos.x += field_relative.x;
    this->pos.y += field_relative.y;
    this->theta += phi;
}

void Odometry::init() {
    this->left->setMode(C_DcMotor::C_RunMode::STOP_AND_RESET_ENCODER);
    this->left->setMode(C_DcMotor::C_RunMode::RUN_WITHOUT_ENCODER);

    this->right->setMode(C_DcMotor::C_RunMode::STOP_AND_RESET_ENCODER);
    this->right->setMode(C_DcMotor::C_RunMode::RUN_WITHOUT_ENCODER);

    if (this->perp != nullptr) {
        this->perp->setMode(C_DcMotor::C_RunMode::STOP_AND_RESET_ENCODER);
        this->perp->setMode(C_DcMotor::C_RunMode::RUN_WITHOUT_ENCODER);
    }

    this->last_update = high_resolution_clock::now();
}