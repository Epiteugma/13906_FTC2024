#include "feedforward.h"

int FeedforwardValues::get_index(double time) {
    double min_distance = 0.0;
    int index = 0;

    for (int i = 0; i < this->time_points.size(); i++) {
        double time_at_point = this->time_points[i];
        double distance = std::abs(time - time_at_point);

        if (i == 0 || distance <= min_distance) {
            min_distance = distance;
            index = i;
        } else break;
    }

    return index;
}