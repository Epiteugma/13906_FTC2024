#include "drive.h"

extern "C"
JNIEXPORT void JNICALL Java_org_firstinspires_ftc_teamcode_opmodes_Drive_runOpMode(JNIEnv *p_jni, jobject self) {
    (new Drive(p_jni, self))->runOpMode();
}

void Drive::runOpMode() {
    auto *front_left = this->hardwareMap->getDcMotor("front_left");
    auto *front_right = this->hardwareMap->getDcMotor("front_right");
    auto *back_left = this->hardwareMap->getDcMotor("back_left");
    auto *back_right = this->hardwareMap->getDcMotor("back_right");

    front_left->setDirection(C_DcMotor::C_Direction::REVERSE);
    front_right->setDirection(C_DcMotor::C_Direction::REVERSE);
    back_right->setDirection(C_DcMotor::C_Direction::REVERSE);

    auto *rotate_servo = this->hardwareMap->getServo("rotate");
    auto *extend_servo = this->hardwareMap->getServo("extend");
    auto *pickup_servo = this->hardwareMap->getServo("pickup");

    this->waitForStart();

    while (this->opModeIsActive()) {
        float forward_power = -this->gamepad1->left_stick_y();
        float strafe_power = this->gamepad1->left_stick_x();
        float turn_power = this->gamepad1->right_stick_x();

        front_left->setPower((double) (forward_power + turn_power + strafe_power));
        front_right->setPower((double) (forward_power - turn_power - strafe_power));
        back_left->setPower((double) (forward_power + turn_power - strafe_power));
        back_right->setPower((double) (forward_power - turn_power + strafe_power));

        if (this->gamepad1->a()) {
            //rotate_servo->setPosition(0.85);
            //extend_servo->setPosition(0.7);
            //pickup_servo->setPosition(1.0);
        } else if (this->gamepad1->b()) {
            //rotate_servo->setPosition(0.1);
            //extend_servo->setPosition(0.0);
            //pickup_servo->setPosition(0.0);
        }
    }
}