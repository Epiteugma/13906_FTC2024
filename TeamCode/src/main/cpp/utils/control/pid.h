#pragma once
#include <chrono>
#include <utils/maths.h>

class PID {
    double it = 0.0;
    double p_error = 0.0;
public:
    maths::vec3 coefficients;
    PID(double kP, double kI, double kD);

    double update(double error, std::chrono::duration<double> delta_time = std::chrono::duration<double>(0.0));
    void reset();
};