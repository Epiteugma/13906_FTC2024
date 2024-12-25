#pragma once
#include "../lib/hardware/c_dc_motor.h"
#include "maths.h"

struct Odometry {
    C_DcMotor *left{};
    C_DcMotor *right{};
    C_DcMotor *parallel{};

    float track_width = 0.0;
    float perp_offset = 0.0;

    math::vec2 pos{};
    double theta = 0.0;

    void reset_deltas();
    void update();
private:
    int last_left = 0;
    int last_right = 0;
    int last_parallel = 0;
};