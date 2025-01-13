#include "auton.h"

extern "C"
JNIEXPORT void JNICALL
Java_org_firstinspires_ftc_teamcode_opmodes_Auton_runOpMode(JNIEnv *p_jni, jobject self) {
    (new Auton(p_jni, self))->runOpMode();
}

void Auton::init() {
    this->drivetrain = {
            this->hardwareMap->getDcMotor("front_left"),
            this->hardwareMap->getDcMotor("front_right"),
            this->hardwareMap->getDcMotor("back_left"),
            this->hardwareMap->getDcMotor("back_right")
    };

    this->lift_1 = this->hardwareMap->getDcMotor("lift_1");
    this->lift_2 = this->hardwareMap->getDcMotor("lift_2");
    this->lift_2->setDirection(C_DcMotor::C_Direction::REVERSE);

    this->basket_servo = this->hardwareMap->getServo("basket");
    this->rotate_servo = this->hardwareMap->getServo("rotate");

    this->drivetrain.front_left->setDirection(C_DcMotor::C_Direction::REVERSE);
    this->drivetrain.front_right->setDirection(C_DcMotor::C_Direction::REVERSE);
    this->drivetrain.back_right->setDirection(C_DcMotor::C_Direction::REVERSE);

    this->odometry = {
            this->drivetrain.back_left,
            this->hardwareMap->getDcMotor("right_encoder"),
            drivetrain.front_left,
            15.0 * ODOMETRY_TICKS_PER_CM,
            12.5 * ODOMETRY_TICKS_PER_CM
    };

    this->odometry.right->setDirection(C_DcMotor::C_Direction::REVERSE);

    this->extend_motor = this->hardwareMap->getDcMotor("extend");
    this->extend_motor->setDirection(C_DcMotor::C_Direction::REVERSE);

    this->extend_motor->setTargetPosition(EXTEND_MAX_DEGREES / -360.0 * EXTEND_TICKS_PER_REV);
    this->extend_motor->setMode(C_DcMotor::C_RunMode::STOP_AND_RESET_ENCODER);
    this->extend_motor->setMode(C_DcMotor::C_RunMode::RUN_TO_POSITION);
}

void Auton::runOpMode() {
    math::vec3 path[] = {
        {-35.0, 0.0, 0.0},
        {-40.0, -45.0, -35.0},
        {-40.0 + 35 * std::sin(35.0 / 180.0 * M_PI), -45.0 - 35 * std::cos(35.0 / 180.0 * M_PI), -35.0},
        {-50.0, -28.0, 0.0},
        {-50.0, -28.0, -140.0},
        //{-50.0, 200.0, 0.0},
        //{5.0, 200.0, 0.0}
    };

    double turn_thresh = 2.0;
    double x_thresh = 7.0;
    double y_thresh = 7.0;

    PID pid[] = {
            {1.0 / 20.0},
            {1.0 / 20.0},
            {1.0 / 20.0}
    };

    int node_index = 0;
    time_point<high_resolution_clock> basket_reached_at;

    this->init();

    this->waitForStart();
    this->odometry.init();

    this->lift_1->setTargetPosition(0);
    this->lift_2->setTargetPosition(0);

    this->lift_1->setMode(C_DcMotor::C_RunMode::STOP_AND_RESET_ENCODER);
    this->lift_2->setMode(C_DcMotor::C_RunMode::STOP_AND_RESET_ENCODER);

    this->lift_1->setMode(C_DcMotor::C_RunMode::RUN_TO_POSITION);
    this->lift_2->setMode(C_DcMotor::C_RunMode::RUN_TO_POSITION);

    this->extend_motor->setPower(1.0);

    this->rotate_servo->setPosition(ROTATE_SERVO_MID);
    this->basket_servo->setPosition(BASKET_SERVO_COLLECT);

    while (this->opModeIsActive()) {
        math::vec3 target = path[node_index];

        math::vec3 pid_values = {
                pid[0].update(target.x, odometry.pos.x / ODOMETRY_TICKS_PER_CM),
                pid[1].update(target.y, odometry.pos.y / ODOMETRY_TICKS_PER_CM),
                pid[2].update(target.z, -odometry.theta / M_PI * 180.0),
        };

        math::vec2 xy = pid_values.xy();
        xy.rotate(-odometry.theta);

        pid_values.x = xy.x;
        pid_values.y = xy.y;

        this->strafe_power = pid_values.x;
        this->forward_power = pid_values.y;
        this->turn_power = pid_values.z;

        this->drivetrain.drive(
                this->forward_power,
                this->strafe_power,
                this->turn_power
        );

        double turn_err = std::abs(target.z + odometry.theta / M_PI * 180);
        double x_err = std::abs(target.x - (odometry.pos.x / ODOMETRY_TICKS_PER_CM));
        double y_err = std::abs(target.y - (odometry.pos.y / ODOMETRY_TICKS_PER_CM));

        double lift_1_err;
        double lift_2_err;
        double lift_err;
        duration<double> basket_delta{};

        if (turn_err < turn_thresh && x_err < x_thresh && y_err < y_thresh) {
            node_index++;

            switch (node_index) {
                case 2:
                    this->lift_1->setTargetPosition((int) (LIFT_UP_POSITION * LIFT_TICKS_PER_CM));
                    this->lift_2->setTargetPosition((int) (LIFT_UP_POSITION * LIFT_TICKS_PER_CM));

                    this->lift_1->setPower(LIFT_UP_MLT);
                    this->lift_2->setPower(LIFT_UP_MLT);

                    lift_1_err = std::abs(LIFT_UP_POSITION - this->lift_1->getCurrentPosition() / LIFT_TICKS_PER_CM);
                    lift_2_err = std::abs(LIFT_UP_POSITION - this->lift_2->getCurrentPosition() / LIFT_TICKS_PER_CM);

                    lift_err = (lift_1_err + lift_2_err) / 2.0;

                    this->telemetry->addLine(utils::sprintf("lift_1_err = %.2f", lift_1_err));
                    this->telemetry->addLine(utils::sprintf("lift_2_err = %.2f", lift_2_err));
                    this->telemetry->addLine(utils::sprintf("lift_err = %.2f", lift_err));

                    if (lift_err > 10.0) node_index--;
                    break;
                case 3:
                    if (basket_reached_at == time_point<high_resolution_clock>())  {
                        basket_reached_at = high_resolution_clock::now();
                    }

                    this->lift_1->setTargetPosition((int) (LIFT_UP_POSITION * LIFT_TICKS_PER_CM));
                    this->lift_2->setTargetPosition((int) (LIFT_UP_POSITION * LIFT_TICKS_PER_CM));

                    this->lift_1->setPower(LIFT_HOLD_POWER);
                    this->lift_2->setPower(LIFT_HOLD_POWER);

                    this->basket_servo->setPosition(BASKET_SERVO_SCORE);

                    basket_delta = high_resolution_clock::now() - basket_reached_at;
                    if (basket_delta.count() < 1.0) node_index--;
                    break;
                case 4:
                    this->basket_servo->setPosition(BASKET_SERVO_COLLECT);

                    this->lift_1->setTargetPosition(0);
                    this->lift_2->setTargetPosition(0);

                    this->lift_1->setPower(0.0);
                    this->lift_2->setPower(0.0);

                    lift_1_err = std::abs(this->lift_1->getCurrentPosition() / LIFT_TICKS_PER_CM);
                    lift_2_err = std::abs(this->lift_2->getCurrentPosition() / LIFT_TICKS_PER_CM);

                    lift_err = (lift_1_err + lift_2_err) / 2.0;

                    this->telemetry->addLine(utils::sprintf("lift_1_err = %.2f", lift_1_err));
                    this->telemetry->addLine(utils::sprintf("lift_2_err = %.2f", lift_2_err));
                    this->telemetry->addLine(utils::sprintf("lift_err = %.2f", lift_err));

                    if (lift_err > 10.0) node_index--;
                    break;
                default:
                    if (node_index >= sizeof(path) / sizeof(math::vec3)) {
                        return;
                    }
                    break;
            }
        }

        this->odometry.update();
        this->printDebugInfo();
    }
}

void Auton::printDebugInfo() {
    this->telemetry->addLine(utils::sprintf(
            "(velocity) x = %.2f; y = %.2f",
            odometry.velocity.x / (ODOMETRY_TICKS_PER_CM * 100.0), // ms-1
            odometry.velocity.y / (ODOMETRY_TICKS_PER_CM * 100.0)
    ));

    this->telemetry->addLine(utils::sprintf(
            "(position) x = %.2f; y = %.2f; θ = %.2f",
            odometry.pos.x / ODOMETRY_TICKS_PER_CM,
            odometry.pos.y / ODOMETRY_TICKS_PER_CM,
            odometry.theta / M_PI * 180.0
    ));

    this->telemetry->addLine(utils::sprintf("forward power = %.2f", this->forward_power));
    this->telemetry->addLine(utils::sprintf("strafe power = %.2f", this->strafe_power));
    this->telemetry->addLine(utils::sprintf("turn power = %.2f", this->turn_power));

    this->telemetry->addLine();
    this->telemetry->addLine(utils::sprintf("lift_1 power = %.2f", this->lift_1->getPower()));
    this->telemetry->addLine(utils::sprintf("lift_2 power = %.2f", this->lift_2->getPower()));

    this->telemetry->update();
}
