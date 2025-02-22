#include "feedforward_test.h"

extern "C"
JNIEXPORT void JNICALL Java_org_firstinspires_ftc_teamcode_opmodes_FeedForwardTest_runOpMode(JNIEnv *p_jni, jobject self) {
    (new FeedForwardTest(p_jni, self))->runOpMode();
}

void FeedForwardTest::runOpMode() {
    this->robot = new Robot(this);

    this->waitForStart();

    // consider an environment without turning
    maths::vec2 target{240.0, 0.0};

    auto start = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed(0.0);

    // assuming linear movement, for curve - integrate
    double distance_to_cover = std::hypot(target[0], target[1]) / 100.0; // in meters
    double angle = std::atan2(target[1], target[0]);
    double distance_at_max_velocity = this->max_velocity * this->time_to_max_velocity; // distance travelled by accelerating and then decelerating immediately after

    double velocity_to_reach = std::min(distance_to_cover / distance_at_max_velocity * this->max_velocity, this->max_velocity);
    double time_to_max_vel = velocity_to_reach / this->max_velocity * this->time_to_max_velocity;
    double time_at_max_vel = velocity_to_reach < this->max_velocity ? 0.0 : (distance_to_cover - distance_at_max_velocity) / this->max_velocity;

    double total_path_time = 2 * time_to_max_vel + time_at_max_vel;

    while (this->opModeIsActive()) {
        this->robot->odometry->update(); // TODO: for PID

        auto now = std::chrono::system_clock::now();
        elapsed = now - start;

        double target_velocity = 0.0;
        double distance_covered = distance_to_cover;

        if (elapsed.count() < time_to_max_vel) {
            target_velocity = velocity_to_reach * elapsed.count() / time_to_max_vel;
            distance_covered = target_velocity * elapsed.count() / 2.0;

            this->telemetry->addLine("phase = acceleration");
        } else if (elapsed.count() < time_to_max_vel + time_at_max_vel) {
            target_velocity = velocity_to_reach;
            distance_covered = velocity_to_reach * time_to_max_vel / 2.0 + (elapsed.count() - time_to_max_vel) * velocity_to_reach;

            this->telemetry->addLine("phase = constant speed");
        } else if (elapsed.count() < total_path_time) {
            double decel_time = elapsed.count() - time_to_max_vel - time_at_max_vel;
            target_velocity = velocity_to_reach * (1 - decel_time / time_to_max_vel);

            double decel_distance = (velocity_to_reach * time_to_max_vel / 2.0) - (target_velocity * (time_to_max_vel - decel_time) / 2.0);
            distance_covered = velocity_to_reach * time_to_max_vel / 2.0 + time_at_max_vel * velocity_to_reach + decel_distance;

            this->telemetry->addLine("phase = deceleration");
        }

        // TODO: for PID
        maths::vec2 feedforward_displacement{
            distance_covered * 100.0 * std::cos(angle),
            distance_covered * 100.0 * std::sin(angle),
        };

        maths::vec2 feedforward_velocity{
            target_velocity * std::cos(angle),
            target_velocity * std::sin(angle),
        };

        maths::vec2 wheel_powers{
            this->kS + (feedforward_velocity[1] + feedforward_velocity[0]) * this->kV,
            this->kS + (feedforward_velocity[1] - feedforward_velocity[0]) * this->kV,
        };

        this->robot->drivetrain->front_left->setPower(wheel_powers[0]);
        this->robot->drivetrain->front_right->setPower(wheel_powers[1]);
        this->robot->drivetrain->back_left->setPower(wheel_powers[1]);
        this->robot->drivetrain->back_right->setPower(wheel_powers[0]);

        this->telemetry->addLine(utils::sprintf("expected displacement = (%.2f, %.2f)", feedforward_displacement[0], feedforward_displacement[1]));
        this->telemetry->addLine(utils::sprintf(
            "actual displacement = (%.2f, %.2f)",
            this->robot->odometry->position[0] / ODOMETRY_TICKS_PER_CM,
            this->robot->odometry->position[1] / ODOMETRY_TICKS_PER_CM
        ));
        this->telemetry->addLine();

        this->telemetry->addLine(utils::sprintf("expected velocity = %.2fms-1", target_velocity));
        this->telemetry->addLine();

        this->telemetry->addLine(utils::sprintf("velocity to reach = %.2f", velocity_to_reach));
        this->telemetry->addLine(utils::sprintf("time to max velocity = %.2fs", time_to_max_vel));
        this->telemetry->addLine(utils::sprintf("time at max velocity = %.2fs", time_at_max_vel));
        this->telemetry->addLine(utils::sprintf("total path time = %.2fs", total_path_time));
        this->telemetry->addLine(utils::sprintf("elapsed = %.2fs", elapsed.count()));
        this->telemetry->update();
    }
}