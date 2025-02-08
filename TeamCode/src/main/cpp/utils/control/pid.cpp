#include "pid.h"

PID::PID(double kP, double kI, double kD) {
    this->coefficients[0] = kP;
    this->coefficients[1] = kI;
    this->coefficients[2] = kD;
}

double PID::update(double error, std::chrono::duration<double> delta_time) {
    double p = this->coefficients[0] * error;
    double i = this->coefficients[1] * error * delta_time.count();
    double d = this->coefficients[2] * (error - this->p_error) / delta_time.count();

    this->p_error = error;
    this->it += i;

    return p + this->it + d;
}

void PID::reset() {
    this->it = 0.0;
    this->p_error = 0.0;
}