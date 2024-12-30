#include "maths.h"

void math::vec2::rotate(double theta) {
    double old_x = this->x;
    double old_y = this->y;

    this->x = std::cos(theta) * old_x - std::sin(theta) * old_y;
    this->y = std::sin(theta) * old_x + std::cos(theta) * old_y;
}

double math::ticksToDistance(double ticks, double wheelRadius, int ticksPerRev) {
    return (double) ticks / (double) ticksPerRev * (2 * M_PI * wheelRadius);
}

double math::distanceToTicks(double distance, double wheelRadius, int ticksPerRev) {
    return (int) (distance / (2 * M_PI * wheelRadius) * ticksPerRev);
}