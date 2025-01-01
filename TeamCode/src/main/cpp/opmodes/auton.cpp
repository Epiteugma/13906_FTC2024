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
        drivetrain.back_right,
        16.0 * ODOMETRY_TICKS_PER_CM,
        12.5 * ODOMETRY_TICKS_PER_CM
    };

    this->waitForStart();
    this->odometry.init();

    double targetY = 120.0 * ODOMETRY_TICKS_PER_CM;

    while (this->opModeIsActive()) {
        double progress = odometry.pos.y / targetY;
        auto feed_forward = profiles::paranoia(progress);

        this->forward_power = progress < 0.0 || progress > 1.0 ? 0.0 : std::max(STALL_POWER, feed_forward.power);

        this->drivetrain.drive(
            this->forward_power,
            0.0
        );

        this->odometry.update();
        this->printDebugInfo();
    }
}