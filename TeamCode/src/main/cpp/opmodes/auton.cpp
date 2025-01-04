#include "auton.h"

extern "C"
JNIEXPORT void JNICALL
Java_org_firstinspires_ftc_teamcode_opmodes_Auton_runOpMode(JNIEnv *p_jni, jobject self) {
    (new Auton(p_jni, self))->runOpMode();
}

void Auton::printDebugInfo() {
    this->telemetry->addLine(utils::sprintf(
            "(velocity) x = %.2f; y = %.2f",
            odometry.velocity.x / (ODOMETRY_TICKS_PER_CM * 100.0), // ms-1
            odometry.velocity.y / (ODOMETRY_TICKS_PER_CM * 100.0)
    ));

    this->telemetry->addLine(utils::sprintf(
            "(position) x = %.2f; y = %.2f; θ = %.2f",
            odometry.pos.x / ODOMETRY_TICKS_PER_CM,
            odometry.pos.y / ODOMETRY_TICKS_PER_CM,
            odometry.theta / M_PI * 180.0
    ));

    this->telemetry->addLine(utils::sprintf("forward power = %.2f", this->forward_power));
    this->telemetry->addLine(utils::sprintf("strafe power = %.2f", this->strafe_power));
    this->telemetry->addLine(utils::sprintf("turn power = %.2f", this->turn_power));

    this->telemetry->update();
}

void Auton::runOpMode() {
    this->drivetrain = {
        this->hardwareMap->getDcMotor("front_left"),
        this->hardwareMap->getDcMotor("front_right"),
        this->hardwareMap->getDcMotor("back_left"),
        this->hardwareMap->getDcMotor("back_right")
    };

    this->drivetrain.front_left->setDirection(C_DcMotor::C_Direction::REVERSE);
    this->drivetrain.front_right->setDirection(C_DcMotor::C_Direction::REVERSE);
    this->drivetrain.back_right->setDirection(C_DcMotor::C_Direction::REVERSE);

    this->odometry = {
        this->drivetrain.back_left,
        this->hardwareMap->getDcMotor("right_encoder"),
        drivetrain.front_left,
        16.0 * ODOMETRY_TICKS_PER_CM,
        12.5 * ODOMETRY_TICKS_PER_CM
    };

    this->odometry.right->setDirection(C_DcMotor::C_Direction::REVERSE);

    this->waitForStart();
    this->odometry.init();

    math::vec2 target = {
        0,
        120.0 * ODOMETRY_TICKS_PER_CM
    };

    double target_heading = 0.0;

    // 1 meter error = power 1
    // 90 deg error = power 1
    PID pid[] = {
        {1 / (ODOMETRY_TICKS_PER_CM * 100)},
        {1 / (ODOMETRY_TICKS_PER_CM * 100)},
        {1.0 / (90 / 180.0 * M_PI)}
    };

    while (this->opModeIsActive()) {
        math::vec2 pid_values = {
            pid[0].update(target.x, odometry.pos.x),
            pid[1].update(target.y, odometry.pos.y),
        };

        pid_values.rotate(-odometry.theta);

        this->strafe_power = pid_values.x;
        this->forward_power = pid_values.y;
        this->turn_power = pid[2].update(target_heading, -odometry.theta);

        this->drivetrain.drive(
            this->forward_power,
            this->strafe_power,
            this->turn_power
        );

        this->odometry.update();
        this->printDebugInfo();
    }
}