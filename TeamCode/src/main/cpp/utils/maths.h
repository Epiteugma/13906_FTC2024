#pragma once
#include "cmath"

namespace math {
    struct vec2 {
        double x;
        double y;

        void rotate(double theta);
    };

    struct vec3 {
        double x;
        double y;
        double z;
    };

    double ticksToDistance(double ticks, double wheelRadius, int ticksPerRev);
    double distanceToTicks(double distance, double wheelRadius, int ticksPerRev);
}