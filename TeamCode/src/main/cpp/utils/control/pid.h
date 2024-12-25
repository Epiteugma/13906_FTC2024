#pragma once
#include "chrono"

struct PID {
    double kP = 1.0;
    double kI = 0.0;
    double kD = 0.0;

    double It = 0.0;
    double last_error = 0.0;
    std::chrono::time_point<std::chrono::high_resolution_clock> last_update = std::chrono::high_resolution_clock::now();

    double update(double target, double current);
    void reset();
};