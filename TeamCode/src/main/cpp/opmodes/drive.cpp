#include "drive.h"
#include "../utils/kinematics/drivetrain.h"
#include "../utils/constants.h"

extern "C"
JNIEXPORT void JNICALL Java_org_firstinspires_ftc_teamcode_opmodes_Drive_runOpMode(JNIEnv *p_jni, jobject self) {
    (new Drive(p_jni, self))->runOpMode();
}

void Drive::runOpMode() {
    this->drivetrain = {
        this->hardwareMap->getDcMotor("front_left"),
        this->hardwareMap->getDcMotor("front_right"),
        this->hardwareMap->getDcMotor("back_left"),
        this->hardwareMap->getDcMotor("back_right")
    };

    this->drivetrain.front_left->setDirection(C_DcMotor::C_Direction::REVERSE);
    this->drivetrain.front_right->setDirection(C_DcMotor::C_Direction::REVERSE);
    this->drivetrain.back_right->setDirection(C_DcMotor::C_Direction::REVERSE);

    this->lift_1 = this->hardwareMap->getDcMotor("lift_1");
    this->lift_2 = this->hardwareMap->getDcMotor("lift_2");
    this->lift_2->setDirection(C_DcMotor::C_Direction::REVERSE);

    this->extend_motor = this->hardwareMap->getDcMotor("extend");
    this->extend_motor->setDirection(C_DcMotor::C_Direction::REVERSE);

    this->rotate_servo = this->hardwareMap->getServo("rotate");
    this->pickup_servo = this->hardwareMap->getServo("pickup");
    this->basket_servo = this->hardwareMap->getServo("basket");

    this->waitForStart();

    this->rotate_servo->setPosition(ROTATE_SERVO_UP);
    this->pickup_servo->setPosition(PICKUP_SERVO_CLOSED);
    this->basket_servo->setPosition(BASKET_SERVO_COLLECT);

    while (this->opModeIsActive()) {
        this->drivetrain.drive(
            -this->gamepad1->left_stick_y(),
            this->gamepad1->left_stick_x() ,
            this->gamepad1->right_stick_x()
        );

        if (this->gamepad1->left_bumper()) {
            this->drivetrain.multiplier = 0.25;
        } else if (this->gamepad1->right_bumper()) {
            this->drivetrain.multiplier = 1.0;
        }

        if (this->gamepad2->dpad_up()) {
            this->rotate_servo->setPosition(ROTATE_SERVO_DOWN);
        } else if (this->gamepad2->dpad_down()) {
            this->rotate_servo->setPosition(ROTATE_SERVO_UP);
            this->basket_servo->setPosition(BASKET_SERVO_COLLECT);
        }

        if (this->gamepad2->dpad_left()) {
            this->rotate_servo->setPosition(ROTATE_SERVO_MID);
        }

        if (this->gamepad2->a()) {
            this->pickup_servo->setPosition(PICKUP_SERVO_CLOSED);
        } else if (this->gamepad2->y()) {
            this->pickup_servo->setPosition(PICKUP_SERVO_OPEN);
        }

        if (this->gamepad2->right_bumper()) {
            this->basket_servo->setPosition(BASKET_SERVO_COLLECT);
        } else if (this->gamepad2->left_bumper()) {
            this->basket_servo->setPosition(BASKET_SERVO_SCORE);
        } else if (this->gamepad2->dpad_right()) {
            this->basket_servo->setPosition(BASKET_SERVO_BALANCE);
        }

        float lift_power = -this->gamepad2->left_stick_y();

        if (lift_power == 0.0) {
            if (this->lift_1->getMode() != C_DcMotor::C_RunMode::RUN_TO_POSITION) {
                this->lift_1->setTargetPosition(this->lift_1->getCurrentPosition());
            }

            if (this->lift_2->getMode() != C_DcMotor::C_RunMode::RUN_TO_POSITION) {
                this->lift_2->setTargetPosition(this->lift_2->getCurrentPosition());
            }

            this->lift_1->setMode(C_DcMotor::C_RunMode::RUN_TO_POSITION);
            this->lift_1->setPower(LIFT_HOLD_POWER);

            this->lift_2->setMode(C_DcMotor::C_RunMode::RUN_TO_POSITION);
            this->lift_2->setPower(LIFT_HOLD_POWER);
        } else {
            this->lift_1->setMode(C_DcMotor::C_RunMode::RUN_WITHOUT_ENCODER);
            this->lift_1->setPower(lift_power);

            this->lift_2->setMode(C_DcMotor::C_RunMode::RUN_WITHOUT_ENCODER);
            this->lift_2->setPower(lift_power);
        }

        float extend_power = (this->gamepad2->right_trigger() - this->gamepad2->left_trigger()) * 0.75f;

        if (extend_power == 0.0) {
            if (this->extend_motor->getMode() != C_DcMotor::C_RunMode::RUN_TO_POSITION) {
                this->extend_motor->setTargetPosition(this->extend_motor->getCurrentPosition());
            }

            this->extend_motor->setMode(C_DcMotor::C_RunMode::RUN_TO_POSITION);
            this->extend_motor->setPower(EXTEND_HOLD_POWER);
        } else {
            this->extend_motor->setMode(C_DcMotor::C_RunMode::RUN_WITHOUT_ENCODER);
            this->extend_motor->setPower(extend_power);
        }
    }
}