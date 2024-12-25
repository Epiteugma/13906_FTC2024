#include "pid.h"

double PID::update(double target, double current) {
    auto now = std::chrono::high_resolution_clock::now();
    double delta_time = (double) std::chrono::duration_cast<std::chrono::microseconds>(now - this->last_update).count() / 1000000.0;
    this->last_update = now;

    double error = target - current;

    double p = this->kP * error;
    double i = this->kI * error * delta_time;
    double d = this->kD * (error - this->last_error) / delta_time;

    this->It += i;
    return p + this->It + d;
}

void PID::reset() {
    this->last_update = std::chrono::high_resolution_clock::now();
    this->It = 0.0;
    this->last_error = 0.0;
}