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
        static_cast<float>(math::distanceToTicks(15.0, 3.0, 8192)),
        static_cast<float>(math::distanceToTicks(-15.0, 3.0, 8192))
    };

    this->waitForStart();

    odometry.left->setMode(C_DcMotor::C_RunMode::STOP_AND_RESET_ENCODER);
    odometry.right->setMode(C_DcMotor::C_RunMode::STOP_AND_RESET_ENCODER);
    odometry.perp->setMode(C_DcMotor::C_RunMode::STOP_AND_RESET_ENCODER);

    odometry.left->setMode(C_DcMotor::C_RunMode::RUN_WITHOUT_ENCODER);
    odometry.right->setMode(C_DcMotor::C_RunMode::RUN_WITHOUT_ENCODER);
    odometry.perp->setMode(C_DcMotor::C_RunMode::RUN_WITHOUT_ENCODER);

    odometry.reset_deltas();

    while (this->opModeIsActive()) {
        odometry.update();

        this->telemetry->addLine(utils::sprintf(
            "left = %d; right = %d; perp = %d",
            odometry.left->getCurrentPosition(),
            odometry.right->getCurrentPosition(),
            odometry.perp->getCurrentPosition()
        ));

        this->telemetry->addLine(utils::sprintf(
            "track_width = %.2f; perp_offset = %.2f",
            odometry.track_width,
            odometry.perp_offset
        ));

        this->telemetry->addLine(utils::sprintf(
            "x = %d; y = %d; θ = %.2f",
            odometry.pos.x,
            odometry.pos.y,
            odometry.theta
        ));

        this->telemetry->update();
    }
}