#include "auton.h"
#include "../utils/kinematics/drivetrain.h"
#include "../utils/odometry/odometry.h"
#include "../utils/utils.h"

extern "C"
JNIEXPORT void JNICALL
Java_org_firstinspires_ftc_teamcode_opmodes_Auton_runOpMode(JNIEnv *p_jni, jobject self) {
    (new Auton(p_jni, self))->runOpMode();
}

void Auton::runOpMode() {
    Drivetrain drivetrain{
        this->hardwareMap->getDcMotor("front_left"),
        this->hardwareMap->getDcMotor("front_right"),
        this->hardwareMap->getDcMotor("back_left"),
        this->hardwareMap->getDcMotor("back_right")
    };

    drivetrain.front_left->setDirection(C_DcMotor::C_Direction::REVERSE);
    drivetrain.front_right->setDirection(C_DcMotor::C_Direction::REVERSE);
    drivetrain.back_right->setDirection(C_DcMotor::C_Direction::REVERSE);

    Odometry odometry{
        drivetrain.front_right,
        this->hardwareMap->getDcMotor("right_encoder"),
        drivetrain.back_right,
        static_cast<float>(math::distanceToTicks(17.0, 3.0, 8192)),
        static_cast<float>(math::distanceToTicks(-11.5, 3.0, 8192))
    };

    this->waitForStart();
    odometry.init();

    while (this->opModeIsActive()) {
        odometry.update();

        this->telemetry->addLine(utils::sprintf(
            "(velocity) x = %.2f; y = %.2f",
            math::ticksToDistance(odometry.velocity.x, 0.03, 8192), // ms-1
            math::ticksToDistance(odometry.velocity.y, 0.03, 8192)
        ));

        this->telemetry->addLine(utils::sprintf(
            "(position) x = %.2f; y = %.2f; θ = %.2f",
            math::ticksToDistance(odometry.pos.x, 3.0, 8192),
            math::ticksToDistance(odometry.pos.y, 3.0, 8192),
            odometry.theta / M_PI * 180.0
        ));

        this->telemetry->update();
    }
}