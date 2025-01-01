#pragma once
#include "cmath"

namespace profiles {
    struct point {
        double progress;
        double power;
        double moveProgress;
    };

    point paranoia(double progress);
}