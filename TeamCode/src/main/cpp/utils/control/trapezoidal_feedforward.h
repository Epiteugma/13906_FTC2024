#pragma once
#include <utils/control/feedforward.h>

class TrapezoidalFeedforward {
    double time_to_max_velocity;
public:
    double kS;
    double kV;
    const int num_steps = 100;

    explicit TrapezoidalFeedforward(double kS = 0.0, double kV = 1.0, double time_to_max_velocity = 1.0);
    FeedforwardValues calculate(maths::vec3 end, maths::vec3 start);
};