#pragma once
#include "cmath"

namespace math {
    struct mat2 {
        double value[2][2];
    };

    struct mat3 {
        double value[3][3];
    };

    struct vec2 {
        double x;
        double y;
    };

    struct vec3 {
        double x;
        double y;
        double z;
    };

    mat2 rotationMatrix(double theta);
}