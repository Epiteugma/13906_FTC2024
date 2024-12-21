#include "maths.h"

math::mat2 math::rotationMatrix(double theta) {
    return {
        std::cos(theta), -std::sin(theta),
        std::sin(theta), std::cos(theta)
    };
}