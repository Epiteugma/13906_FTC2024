#include "drive.h"
#include "../utils/kinematics/drivetrain.h"
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

    auto lift_1 = this->hardwareMap->getDcMotor("lift_1");
    auto lift_2 = this->hardwareMap->getDcMotor("lift_2");
    lift_2->setDirection(C_DcMotor::C_Direction::REVERSE);

    auto extend_motor = this->hardwareMap->getDcMotor("extend");
    extend_motor->setDirection(C_DcMotor::C_Direction::REVERSE);

    auto rotate_servo = this->hardwareMap->getServo("rotate");
    auto pickup_servo = this->hardwareMap->getServo("pickup");
    auto basket_servo = this->hardwareMap->getServo("basket");

    this->waitForStart();

    rotate_servo->setPosition(ROTATE_SERVO_UP);
    pickup_servo->setPosition(PICKUP_SERVO_CLOSED);
    basket_servo->setPosition(BASKET_SERVO_COLLECT);

    while (this->opModeIsActive()) {
        drivetrain.drive(
            -this->gamepad1->left_stick_y(),
            this->gamepad1->left_stick_x() ,
            this->gamepad1->right_stick_x()
        );

        if (this->gamepad1->left_bumper()) {
            drivetrain.multiplier = 0.25;
        } else if (this->gamepad1->right_bumper()) {
            drivetrain.multiplier = 1.0;
        }

        if (this->gamepad2->dpad_up()) {
            rotate_servo->setPosition(ROTATE_SERVO_DOWN);
        } else if (this->gamepad2->dpad_down()) {
            rotate_servo->setPosition(ROTATE_SERVO_UP);
            basket_servo->setPosition(BASKET_SERVO_COLLECT);
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
        } else if (this->gamepad2->dpad_right()) {
            basket_servo->setPosition(BASKET_SERVO_BALANCE);
        }

        float lift_power = -this->gamepad2->left_stick_y();

        if (lift_power == 0.0) {
            if (lift_1->getMode() != C_DcMotor::C_RunMode::RUN_TO_POSITION) {
                lift_1->setTargetPosition(lift_1->getCurrentPosition());
            }

            if (lift_2->getMode() != C_DcMotor::C_RunMode::RUN_TO_POSITION) {
                lift_2->setTargetPosition(lift_2->getCurrentPosition());
            }

            lift_1->setMode(C_DcMotor::C_RunMode::RUN_TO_POSITION);
            lift_1->setPower(LIFT_HOLD_POWER);

            lift_2->setMode(C_DcMotor::C_RunMode::RUN_TO_POSITION);
            lift_2->setPower(LIFT_HOLD_POWER);
        } else {
            lift_1->setMode(C_DcMotor::C_RunMode::RUN_WITHOUT_ENCODER);
            lift_1->setPower(lift_power);

            lift_2->setMode(C_DcMotor::C_RunMode::RUN_WITHOUT_ENCODER);
            lift_2->setPower(lift_power);
        }

        float extend_power = (this->gamepad2->right_trigger() - this->gamepad2->left_trigger()) * 0.75f;

        if (extend_power == 0.0) {
            if (extend_motor->getMode() != C_DcMotor::C_RunMode::RUN_TO_POSITION) {
                extend_motor->setTargetPosition(extend_motor->getCurrentPosition());
            }

            extend_motor->setMode(C_DcMotor::C_RunMode::RUN_TO_POSITION);
            extend_motor->setPower(EXTEND_HOLD_POWER);
        } else {
            extend_motor->setMode(C_DcMotor::C_RunMode::RUN_WITHOUT_ENCODER);
            extend_motor->setPower(extend_power);
        }
    }
}