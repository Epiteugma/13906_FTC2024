#include "profiles.h"

double profiles::trapezoid(double displacement, double setpoint) {
    double progress = displacement / setpoint;

    if (progress < 0 || progress > 1) return 0;

    if (progress < 0.2) {
        return progress / 0.2;
    }

    if (progress > 0.8) {
        return (1 - progress) / 0.2;
    }

    return 1;
}