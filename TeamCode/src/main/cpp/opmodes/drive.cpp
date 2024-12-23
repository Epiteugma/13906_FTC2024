#include "drive.h"
#include "../utils/drivetrain.h"
#include "../utils/constants.h"

extern "C"
JNIEXPORT void JNICALL Java_org_firstinspires_ftc_teamcode_opmodes_Drive_runOpMode(JNIEnv *p_jni, jobject self) {
    (new Drive(p_jni, self))->runOpMode();
}

void Drive::runOpMode() {
    Drivetrain drivetrain{
        this->hardwareMap->getDcMotor("front_left"),
        this->hardwareMap->getDcMotor("front_right"),
        this->hardwareMap->getDcMotor("back_left"),
        this->hardwareMap->getDcMotor("back_right")
    };

    drivetrain.front_left->setDirection(C_DcMotor::C_Direction::REVERSE);
    drivetrain.front_right->setDirection(C_DcMotor::C_Direction::REVERSE);
    drivetrain.back_right->setDirection(C_DcMotor::C_Direction::REVERSE);

    auto lift = this->hardwareMap->getDcMotor("lift");

    auto rotate_servo = this->hardwareMap->getServo("rotate");
    auto extend_servo = this->hardwareMap->getServo("extend");
    auto pickup_servo = this->hardwareMap->getServo("pickup");
    auto basket_servo = this->hardwareMap->getServo("basket");

    this->waitForStart();

    rotate_servo->setPosition(ROTATE_SERVO_UP);
    extend_servo->setPosition(EXTEND_SERVO_RETRACTED);
    pickup_servo->setPosition(PICKUP_SERVO_CLOSED);
    basket_servo->setPosition(BASKET_SERVO_COLLECT);

    while (this->opModeIsActive()) {
        drivetrain.drive(
            -this->gamepad1->left_stick_y(),
            this->gamepad1->left_stick_x() ,
            this->gamepad1->right_stick_x()
        );

        if (this->gamepad1->square()) {
            drivetrain.multiplier = 0.5;
        } else if (this->gamepad1->circle()) {
            drivetrain.multiplier = 1.0;
        }

        if (this->gamepad2->dpad_up()) {
            rotate_servo->setPosition(ROTATE_SERVO_DOWN);
            extend_servo->setPosition(EXTEND_SERVO_EXTENDED);
        } else if (this->gamepad2->dpad_down()) {
            rotate_servo->setPosition(ROTATE_SERVO_UP);
            extend_servo->setPosition(EXTEND_SERVO_RETRACTED);
        }

        if (this->gamepad2->dpad_left()) {
            rotate_servo->setPosition(ROTATE_SERVO_MID);
        }

        if (this->gamepad2->a()) {
            pickup_servo->setPosition(PICKUP_SERVO_CLOSED);
        } else if (this->gamepad2->y()) {
            pickup_servo->setPosition(PICKUP_SERVO_OPEN);
        }

        if (this->gamepad2->right_bumper()) {
            basket_servo->setPosition(BASKET_SERVO_COLLECT);
        } else if (this->gamepad2->left_bumper()) {
            basket_servo->setPosition(BASKET_SERVO_SCORE);
        }

        float lift_power = -this->gamepad2->left_stick_y();

        if (lift_power == 0.0) {
            if (lift->getMode() != C_DcMotor::C_RunMode::RUN_TO_POSITION) {
                lift->setTargetPosition(lift->getCurrentPosition());
            }

            lift->setMode(C_DcMotor::C_RunMode::RUN_TO_POSITION);
            lift->setPower(LIFT_HOLD_POWER);
        } else {
            lift->setMode(C_DcMotor::C_RunMode::RUN_WITHOUT_ENCODER);
            lift->setPower(lift_power);
        }

    }
}