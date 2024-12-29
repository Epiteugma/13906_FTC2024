#pragma once
#include "cmath"

namespace math {
    struct mat2 {
        double value[2][2] = {
            0.0,0.0,
            0.0, 0.0
        };
    };

    struct mat3 {
        double value[3][3] = {
            0.0, 0.0, 0.0,
            0.0, 0.0, 0.0,
            0.0, 0.0, 0.0
        };
    };

    struct vec2 {
        double x = 0.0;
        double y = 0.0;
    };

    struct vec3 {
        double x = 0.0;
        double y = 0.0;
        double z = 0.0;
    };

    mat2 rotationMatrix(double theta);
    double ticksToDistance(int ticks, double wheelRadius, int ticksPerRev);
    int distanceToTicks(double distance, double wheelRadius, int ticksPerRev);
}