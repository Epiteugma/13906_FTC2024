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

    math::vec2 vec{
        delta_perp + (phi * this->perp_offset),
        (delta_right + delta_left) / 2.0,
    };

    vec.rotate(this->theta);

    this->velocity.x = vec.x / delta_time.count();
    this->velocity.y = vec.y / delta_time.count();

    this->pos.x += vec.x;
    this->pos.y += vec.y;
    this->theta += phi;
}

void Odometry::init() {
    this->last_left = this->left->getCurrentPosition();
    this->last_right = this->right->getCurrentPosition();
    this->last_perp = this->perp == nullptr ? 0 : this->perp->getCurrentPosition();
    this->last_update = high_resolution_clock::now();
}