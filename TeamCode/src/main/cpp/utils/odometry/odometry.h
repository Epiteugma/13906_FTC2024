#pragma once
#include "../../lib/hardware/c_dc_motor.h"
#include "../maths.h"
#include "chrono"

using std::chrono::time_point;
using std::chrono::high_resolution_clock;
using std::chrono::duration;

struct Odometry {
    C_DcMotor *left{};
    C_DcMotor *right{};
    C_DcMotor *perp{};

    float track_width = 0.0;
    float perp_offset = 0.0;

    math::vec2 pos{};
    math::vec2 velocity{};
    double theta = 0.0;

    void reset_deltas();
    void update();

    int last_left = 0;
    int last_right = 0;
    int last_perp = 0;
    time_point<high_resolution_clock> last_update = high_resolution_clock::now();
};