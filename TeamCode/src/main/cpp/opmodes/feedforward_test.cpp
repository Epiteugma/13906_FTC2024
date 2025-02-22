#include "feedforward_test.h"

extern "C"
JNIEXPORT void JNICALL Java_org_firstinspires_ftc_teamcode_opmodes_FeedForwardTest_runOpMode(JNIEnv *p_jni, jobject self) {
    (new FeedForwardTest(p_jni, self))->runOpMode();
}

void FeedForwardTest::runOpMode() {
    this->robot = new Robot(this);
    this->ff = new TrapezoidalFeedforward(0.081316, 0.259461, 1.0);

    this->waitForStart();

    maths::vec3 target{0.0, 2.4, 0.0}; // in meters since kV is for ms-1
    double dir_angle = std::atan2(target[1], target[0]); // TODO: will be given by ff controller
    auto values = this->ff->calculate(target, maths::vec3{});

    auto start = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed(0.0);

    while (this->opModeIsActive()) {
        this->robot->odometry->update(); // TODO: for PID

        auto now = std::chrono::system_clock::now();
        elapsed = now - start;

        int value_index = values.get_index(elapsed.count());

        // TODO: for PID
        maths::vec3 feedforward_displacement{
            values.displacements[value_index * 3],
            values.displacements[value_index * 3 + 1],
            values.displacements[value_index * 3 + 2],
        };

        maths::vec2 feedforward_velocity{
            values.velocities[value_index] * std::cos(dir_angle),
            values.velocities[value_index] * std::sin(dir_angle),
        };

        maths::vec2 wheel_powers{
            this->ff->kS + (feedforward_velocity[1] + feedforward_velocity[0]) * this->ff->kV,
            this->ff->kS + (feedforward_velocity[1] - feedforward_velocity[0]) * this->ff->kV,
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

        this->telemetry->addLine(utils::sprintf("feedforward velocity = (%.2f, %.2f)", feedforward_velocity[0], feedforward_velocity[1]));
        this->telemetry->addLine(utils::sprintf("expected velocity = %.2fms-1", values.velocities[value_index]));
        this->telemetry->addLine(utils::sprintf("elapsed = %.2fs", elapsed.count()));
        this->telemetry->update();
    }
}