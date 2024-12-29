#include "odometry.h"

void Odometry::update() {
    int delta_left = this->left->getCurrentPosition() - this->last_left;
    int delta_right = this->right->getCurrentPosition() - this->last_right;
    int delta_perp = (this->perp == nullptr ? 0 : this->perp->getCurrentPosition()) - this->last_perp;
    //duration<double> delta_time = high_resolution_clock::now() - this->last_update;

    this->reset_deltas();

    double phi = (double) (delta_right - delta_left) / this->track_width;
    double delta_y = ((delta_right + delta_left) / 2.0);
    double delta_x = delta_perp - (phi * this->perp_offset);

    math::vec2 vec{};
    math::mat2 rot = math::rotationMatrix(this->theta);

    vec.x = rot.value[0][0] * delta_x + rot.value[0][1] * delta_y;
    vec.y = rot.value[1][0] * delta_x + rot.value[1][1] * delta_y;

    //this->velocity.x = vec.x / delta_time.count();
    //this->velocity.y = vec.y / delta_time.count();

    this->pos.x += vec.x;
    this->pos.y += vec.y;
    this->theta += phi;
}

void Odometry::reset_deltas() {
    this->last_left = this->left->getCurrentPosition();
    this->last_right = this->right->getCurrentPosition();
    this->last_perp = this->perp == nullptr ? 0 : this->perp->getCurrentPosition();
    //this->last_update = high_resolution_clock::now();
}