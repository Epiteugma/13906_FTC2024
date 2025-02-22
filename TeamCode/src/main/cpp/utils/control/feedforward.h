#pragma once
#include <vector>
#include <utils/maths.h>

struct FeedforwardValues {
    std::vector<double> time_points;
    std::vector<double> velocities;
    std::vector<double> displacements;

    int get_index(double time);
};