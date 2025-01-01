#include "profiles.h"

profiles::point profiles::paranoia(double progress) {
    if (progress < 0.0 || progress > 1.0) {
        return {
            progress,
            0.0,
            progress > 1.0 ? 1.0 : 0.0
        };
    }

    double power = std::sin(progress * M_PI) * 0.5;

    return {
        progress,
        power,
        0.5 * (-std::cos(progress * M_PI) + 1) // - (-cos(0))
    };
}