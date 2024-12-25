#pragma once
#include "chrono"

using std::chrono::time_point;
using std::chrono::high_resolution_clock;
using std::chrono::duration;

struct PID {
    double kP = 1.0;
    double kI = 0.0;
    double kD = 0.0;

    double It = 0.0;
    double last_error = 0.0;
    time_point<high_resolution_clock> last_update = high_resolution_clock::now();

    double update(double target, double current);
    void reset();
};