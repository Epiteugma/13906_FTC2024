#pragma once
#include "../lib/hardware/c_dc_motor.h"
#include "maths.h"

struct Odometry {
    C_DcMotor *left{};
    C_DcMotor *right{};
    C_DcMotor *parallel{};

    math::vec2 pos{};
    float theta = 0.0;

    void update() const;
};