#include "trapezoidal_feedforward.h"

TrapezoidalFeedforward::TrapezoidalFeedforward(double kS, double kV, double time_to_max_velocity) {
    this->kS = kS;
    this->kV = kV;
    this->time_to_max_velocity = time_to_max_velocity;
}

FeedforwardValues TrapezoidalFeedforward::calculate(maths::vec3 end, maths::vec3 start) {
    maths::vec3 dir{
        end[0] - start[0],
        end[1] - start[1],
        end[2] - start[2],
    };

    FeedforwardValues values{
        std::vector<double>(this->num_steps),
        std::vector<double>(this->num_steps),
        std::vector<double>(this->num_steps * 3),
    };

    double max_velocity = (1.0 - this->kS) / this->kV;
    double min_distance_with_max_vel = max_velocity * this->time_to_max_velocity;

    // TODO: integrate
    double distance_to_travel = std::hypot(dir[0], dir[1]);
    double dir_angle = std::atan2(dir[1], dir[0]);

    double max_path_velocity;
    double time_to_max_path_velocity;
    double time_at_max_velocity = 0.0;

    if (distance_to_travel < min_distance_with_max_vel) {
        max_path_velocity = distance_to_travel / min_distance_with_max_vel * max_velocity;
        time_to_max_path_velocity = max_path_velocity / max_velocity * this->time_to_max_velocity;
    } else {
        max_path_velocity = max_velocity;
        time_to_max_path_velocity = this->time_to_max_velocity;
        time_at_max_velocity = (distance_to_travel - min_distance_with_max_vel) / max_velocity;
    }

    double decel_timestamp = time_to_max_path_velocity + time_at_max_velocity;
    double total_time = 2 * time_to_max_path_velocity + time_at_max_velocity;

    for (int i = 0; i < this->num_steps; i++) {
        double timestamp = (double) i / (double) this->num_steps * total_time;
        values.time_points.push_back(timestamp);

        double distance_covered;

        if (timestamp < time_to_max_path_velocity) {
            values.velocities.push_back(timestamp / time_to_max_path_velocity * max_path_velocity);
            distance_covered = values.velocities[i] * timestamp * 0.5;
        } else if (timestamp < decel_timestamp) {
            values.velocities.push_back(max_path_velocity);
            distance_covered = (max_path_velocity * time_to_max_path_velocity * 0.5) + (decel_timestamp - time_to_max_path_velocity) * max_path_velocity;
        } else {
            double decel_time = timestamp - decel_timestamp;
            double remaining_decel_progress = 1 - (decel_time / time_to_max_path_velocity);
            double remaining_distance = (remaining_decel_progress * max_path_velocity) * (remaining_decel_progress * time_to_max_path_velocity) * 0.5;

            values.velocities.push_back((1 - decel_time / time_to_max_path_velocity) * max_path_velocity);
            distance_covered = distance_to_travel - remaining_distance;
        }

        // TODO: integrate
        values.displacements.push_back(start[0] + distance_covered * std::cos(dir_angle));
        values.displacements.push_back(start[1] + distance_to_travel * std::sin(dir_angle));
        values.displacements.push_back(start[2] + dir[2] * timestamp / total_time);
    }

    return values;
}