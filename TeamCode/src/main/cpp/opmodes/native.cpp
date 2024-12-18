#include "native.h"

void Native::runOpMode() {
    auto *front_left = this->hardwareMap->getDcMotor("frontLeft");
    auto *front_right = this->hardwareMap->getDcMotor("frontRight");
    auto *back_left = this->hardwareMap->getDcMotor("backLeft");
    auto *back_right = this->hardwareMap->getDcMotor("backRight");

    this->waitForStart();

    while (this->opModeIsActive()) {
        float forward_power = -this->gamepad1->left_stick_y();
        float strafe_power = this->gamepad1->left_stick_x();
        float turn_power = this->gamepad1->right_stick_x();

        front_left->setPower((double) (forward_power + turn_power + strafe_power));
        front_right->setPower((double) (forward_power - turn_power - strafe_power));
        back_left->setPower((double) (forward_power + turn_power - strafe_power));
        back_right->setPower((double) (forward_power - turn_power + strafe_power));
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_org_firstinspires_ftc_teamcode_test_Native_runOpMode(JNIEnv *p_jni, jobject self) {
    auto *opMode = new Native(p_jni, self);
    opMode->runOpMode();
}