#include "pid.h"

double PID::update(double target, double current) {
    auto now = high_resolution_clock::now();
    duration<double> delta_time = now - this->last_update;
    this->last_update = now;

    double error = target - current;

    double p = this->kP * error;
    double i = this->kI * error * delta_time.count();
    double d = this->kD * (error - this->last_error) / delta_time.count();

    this->It += i;
    return p + this->It + d;
}

void PID::reset() {
    this->last_update = high_resolution_clock::now();
    this->It = 0.0;
    this->last_error = 0.0;
}