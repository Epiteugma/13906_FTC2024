#pragma once
#include <cmath>
#include <lib/hardware/c_dc_motor.h>
#include <utils/maths.h>

class Odometry {
    maths::vec3 last_encoder_values{};
public:
    C_DcMotor *left_encoder;
    C_DcMotor *right_encoder;
    C_DcMotor *perp_encoder;

    double track_width;
    double perp_offset;
    bool enable_integrator = true;

    Odometry(C_DcMotor *left_encoder, C_DcMotor *right_encoder, C_DcMotor *perp_encoder, double track_width, double perp_offset);

    maths::vec3 position{};

    void update();
    void reset();
};