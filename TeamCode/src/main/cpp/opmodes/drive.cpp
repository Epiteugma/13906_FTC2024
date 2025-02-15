#include "drive.h"

extern "C"
JNIEXPORT void JNICALL Java_org_firstinspires_ftc_teamcode_opmodes_Drive_runOpMode(JNIEnv *p_jni, jobject self) {
    (new Drive(p_jni, self))->runOpMode();
}

void Drive::runOpMode() {
    this->robot = new Robot(this);

    this->waitForStart();

    this->rotate_position = ROTATE_SERVO_UP;
    this->pickup_position = PICKUP_SERVO_CLOSED;
    this->basket_position = BASKET_SERVO_COLLECT;
    this->retract_arm();

    while (this->opModeIsActive()) {
        this->move_base();

#ifndef PRACTICE_BOT // ONLY RUNS ON REAL BOT
        this->robot->rotate_servo->setPosition(this->rotate_position);
        this->robot->pickup_servo->setPosition(this->pickup_position);
        this->robot->basket_servo->setPosition(this->basket_position);

        this->robot->extend_motor->setTargetPosition(this->extend_target_position);
        this->robot->extend_motor->setPower(this->extend_power);

        this->collection();
        this->placement();
#endif
    }
}

void Drive::move_base() {
    this->robot->drivetrain->drive(maths::vec3{
        -this->gamepad1->left_stick_y(),
        this->gamepad1->right_stick_x() * DRIVETRAIN_TURN_MLT,
        this->gamepad1->left_stick_x(),
    });

    if (this->gamepad1->right_bumper()) {
        this->robot->drivetrain->multiplier = DRIVETRAIN_FAST_MLT;
    } else if (this->gamepad1->left_bumper()) {
        this->robot->drivetrain->multiplier = DRIVETRAIN_SLOW_MLT;
    }
}

void Drive::collection() {
    if (this->gamepad2->dpad_up()) {
        this->extend_arm();
    } else if (this->gamepad2->dpad_down()) {
        this->retract_arm();

        this->rotate_position = ROTATE_SERVO_UP;
        this->pickup_position = PICKUP_SERVO_CLOSED;
    } else if (this->gamepad2->dpad_left()) {
        this->rotate_position = ROTATE_SERVO_MID;
    } else if (this->gamepad2->dpad_right()) {
        this->rotate_position = ROTATE_SERVO_DOWN;
    }

    if (this->gamepad2->y()) {
        this->pickup_position = PICKUP_SERVO_OPEN;
    } else if (this->gamepad2->a()) {
        this->pickup_position = PICKUP_SERVO_CLOSED;
    }
}

void Drive::placement() {
    float lift_power = -this->gamepad2->left_stick_y();

    if (lift_power == 0.0) {
        if (this->robot->lift_1->getMode() != C_DcMotor::RUN_TO_POSITION) {
            this->robot->lift_1->setTargetPosition(this->robot->lift_1->getCurrentPosition());
        }

        if (this->robot->lift_2->getMode() != C_DcMotor::RUN_TO_POSITION) {
            this->robot->lift_2->setTargetPosition(this->robot->lift_2->getCurrentPosition());
        }

        this->robot->lift_1->setMode(C_DcMotor::RUN_TO_POSITION);
        this->robot->lift_1->setPower(LIFT_HOLD_POWER);

        this->robot->lift_2->setMode(C_DcMotor::RUN_TO_POSITION);
        this->robot->lift_2->setPower(LIFT_HOLD_POWER);
    } else {
        if (lift_power > 0.0) lift_power *= LIFT_UP_MLT;
        else lift_power *= LIFT_DOWN_MLT;

        this->robot->lift_1->setMode(C_DcMotor::RUN_WITHOUT_ENCODER);
        this->robot->lift_1->setPower(lift_power);

        this->robot->lift_2->setMode(C_DcMotor::RUN_WITHOUT_ENCODER);
        this->robot->lift_2->setPower(lift_power);
    }

    if (this->gamepad2->right_bumper()) {
        this->basket_position = BASKET_SERVO_SCORE;
    } else if (this->gamepad2->square()) {
        this->basket_position = BASKET_SERVO_BALANCE;
    } else if (this->gamepad2->left_bumper()) {
        this->basket_position = BASKET_SERVO_COLLECT;
    }
}

void Drive::extend_arm() {
    this->extend_target_position = EXTEND_MAX_DEGREES / 360.0 * EXTEND_TICKS_PER_REV;
    this->extend_power = EXTEND_FORW_POWER;
}

void Drive::retract_arm() {
    this->extend_target_position = EXTEND_MAX_DEGREES / -360.0 * EXTEND_TICKS_PER_REV;
    this->extend_power = EXTEND_BACK_POWER;
}