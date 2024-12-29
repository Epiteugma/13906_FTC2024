#include "maths.h"

math::mat2 math::rotationMatrix(double theta) {
    return {
        std::cos(theta), -std::sin(theta),
        std::sin(theta), std::cos(theta)
    };
}

double math::ticksToDistance(int ticks, double wheelRadius, int ticksPerRev) {
    return (double) ticks / (double) ticksPerRev * (2 * M_PI * wheelRadius);
}

int math::distanceToTicks(double distance, double wheelRadius, int ticksPerRev) {
    return (int) (distance / (2 * M_PI * wheelRadius) * ticksPerRev);
}