#include "robot.h"

Robot::Robot(C_OpMode *op_mode) {
    this->drivetrain = new Drivetrain(
        op_mode->hardwareMap->getDcMotor("front_left"),
        op_mode->hardwareMap->getDcMotor("front_right"),
        op_mode->hardwareMap->getDcMotor("back_left"),
        op_mode->hardwareMap->getDcMotor("back_right")
    );

#ifdef PRACTICE_BOT
    this->drivetrain->front_left->setDirection(C_DcMotor::REVERSE);
    this->drivetrain->front_right->setDirection(C_DcMotor::REVERSE);

    this->odometry = new Odometry(
        op_mode->hardwareMap->getDcMotor("left_encoder"),
        op_mode->hardwareMap->getDcMotor("right_encoder"),
        op_mode->hardwareMap->getDcMotor("perp_encoder"),
        ODOMETRY_TRACK_WIDTH * ODOMETRY_TICKS_PER_CM,
        ODOMETRY_PERP_OFFSET * ODOMETRY_TICKS_PER_CM
    );

    this->odometry->right_encoder->setDirection(C_DcMotor::REVERSE);
    this->odometry->perp_encoder->setDirection(C_DcMotor::REVERSE);
#else
    this->drivetrain->front_left->setDirection(C_DcMotor::REVERSE);
    this->drivetrain->front_right->setDirection(C_DcMotor::REVERSE);
    this->drivetrain->back_right->setDirection(C_DcMotor::REVERSE);

    this->odometry = new Odometry(
        this->drivetrain->back_left,
        op_mode->hardwareMap->getDcMotor("right_encoder"),
        this->drivetrain->front_left,
        ODOMETRY_TRACK_WIDTH * ODOMETRY_TICKS_PER_CM,
        ODOMETRY_PERP_OFFSET * ODOMETRY_TICKS_PER_CM
    );

    this->odometry->right_encoder->setDirection(C_DcMotor::REVERSE);

    this->lift_1 = op_mode->hardwareMap->getDcMotor("lift_1");
    this->lift_2 = op_mode->hardwareMap->getDcMotor("lift_2");

    this->lift_2->setDirection(C_DcMotor::REVERSE);

    this->extend_motor = op_mode->hardwareMap->getDcMotor("extend");
    this->extend_motor->setDirection(C_DcMotor::REVERSE);

    this->extend_motor->setTargetPosition(EXTEND_MAX_DEGREES / -360.0 * EXTEND_TICKS_PER_REV);
    this->extend_motor->setMode(C_DcMotor::STOP_AND_RESET_ENCODER);
    this->extend_motor->setMode(C_DcMotor::RUN_TO_POSITION);

    this->rotate_servo = op_mode->hardwareMap->getServo("rotate");
    this->pickup_servo = op_mode->hardwareMap->getServo("pickup");
    this->basket_servo = op_mode->hardwareMap->getServo("basket");
#endif

    this->odometry->enable_integrator = false;
    this->odometry->reset();
}