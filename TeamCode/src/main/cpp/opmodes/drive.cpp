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

    this->extend_motor->setTargetPosition(EXTEND_MAX_DEGREES / -360.0 * EXTEND_TICKS_PER_REV);
    this->extend_motor->setMode(C_DcMotor::C_RunMode::STOP_AND_RESET_ENCODER);
    this->extend_motor->setMode(C_DcMotor::C_RunMode::RUN_TO_POSITION);

    this->rotate_servo = this->hardwareMap->getServo("rotate");
    this->pickup_servo = this->hardwareMap->getServo("pickup");
    this->basket_servo = this->hardwareMap->getServo("basket");

    this->waitForStart();

    this->rotate_position = ROTATE_SERVO_UP;
    this->pickup_position = PICKUP_SERVO_CLOSED;
    this->basket_position = BASKET_SERVO_COLLECT;
    this->extend_power = EXTEND_BACK_POWER;

    while (this->opModeIsActive()) {
        this->moveBase();

        // anything not set in a loop dies
        // when the battery level is too low
        // hence, we store state manually

        this->rotate_servo->setPosition(this->rotate_position);
        this->pickup_servo->setPosition(this->pickup_position);
        this->basket_servo->setPosition(this->basket_position);
        this->extend_motor->setPower(this->extend_power);

        this->collection();
        this->placement();
    }
}

void Drive::moveBase() {
    this->drivetrain.drive(
        -this->gamepad1->left_stick_y(),
        this->gamepad1->left_stick_x(),
        this->gamepad1->right_stick_x() * DRIVETRAIN_TURN_MLT
    );

    if (this->gamepad1->left_bumper()) {
        this->drivetrain.multiplier = DRIVETRAIN_SLOW_MLT;
    } else if (this->gamepad1->right_bumper()) {
        this->drivetrain.multiplier = DRIVETRAIN_FAST_MLT;
    }
}

void Drive::extendExtension() {
    this->extend_motor->setTargetPosition(EXTEND_MAX_DEGREES / 360.0 * EXTEND_TICKS_PER_REV);
    this->extend_power = EXTEND_FORW_POWER;
}

void Drive::retractExtension() {
    this->extend_motor->setTargetPosition(EXTEND_MAX_DEGREES / -360.0 * EXTEND_TICKS_PER_REV);
    this->extend_power = EXTEND_BACK_POWER;
}

// collection is driver 1's responsibility...
void Drive::collection() {
    // extend rides until stall (may drain power)
    // bad? yes. reliable? very

    // i prefer devving with xbox gamepad buttons
    // A = down, B = right, Y = up, X = left
    if (this->gamepad2->dpad_up()) { // far away pickup
        this->extendExtension();


    } else if (this->gamepad2->dpad_down()) { // retract + deposit into basket
        this->retractExtension();

        this->rotate_position = ROTATE_SERVO_UP;
        this->pickup_position = PICKUP_SERVO_CLOSED; // safety, prevents potential damage to basket
    } else if (this->gamepad2->dpad_left()) { // middle position, any gamepad to allow fast lifting
        this->rotate_position = ROTATE_SERVO_MID;
    } else if (this->gamepad2->dpad_right()) { // close-up pickup


        this->rotate_position = ROTATE_SERVO_DOWN;
    }

    if (this->gamepad2->y()) {
        this->pickup_position = PICKUP_SERVO_OPEN;
    } else if (this->gamepad2->a()) {
        this->pickup_position = PICKUP_SERVO_CLOSED;
    }
}

// ...while placement is driver 2's responsibility
void Drive::placement() {
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
        if (lift_power > 0.0) lift_power *= LIFT_UP_MLT;
        else lift_power *= LIFT_DOWN_MLT;

        this->lift_1->setMode(C_DcMotor::C_RunMode::RUN_WITHOUT_ENCODER);
        this->lift_1->setPower(lift_power);

        this->lift_2->setMode(C_DcMotor::C_RunMode::RUN_WITHOUT_ENCODER);
        this->lift_2->setPower(lift_power);
    }

    if (this->gamepad2->right_bumper()) {
        this->basket_position = BASKET_SERVO_SCORE;
    } else if (this->gamepad2->square()) {
        this->basket_position = BASKET_SERVO_BALANCE;
    } else if (this->gamepad2->left_bumper()) {
        this->basket_position = BASKET_SERVO_COLLECT;
    }
}