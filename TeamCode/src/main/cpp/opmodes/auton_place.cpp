#include "auton.h"



extern "C"
JNIEXPORT void JNICALL Java_org_firstinspires_ftc_teamcode_opmodes_AutonPlace_runOpMode(JNIEnv *p_jni, jobject self) {
    std::vector<math::vec3> path = {
        {-35.0, 0.0, 0.0},
        {-32.0, -45.0, -35.0},
        {-32.0 + 37 * std::sin(35.0 / 180.0 * M_PI), -35.0 - 37 * std::cos(35.0 / 180.0 * M_PI), -40.0},
        {-32.0 + 20 * std::sin(35.0 / 180.0 * M_PI), -35.0 - 20 * std::cos(35.0 / 180.0 * M_PI), -40.0},
        {-80.0, 0.0, 0.0},
        {-90.0, 5.0, -185.0},
        {-85.0, -5.0, -185.0},
        {-40.0 + 20 * std::sin(35.0 / 180.0 * M_PI), -47.0 - 20 * std::cos(35.0 / 180.0 * M_PI), -40.0},
        {-40.0 + 35 * std::sin(35.0 / 180.0 * M_PI), -47.0 - 35 * std::cos(35.0 / 180.0 * M_PI), -40.0},
        {-40.0 + 20 * std::sin(35.0 / 180.0 * M_PI), -47.0 - 20 * std::cos(35.0 / 180.0 * M_PI), -40.0},
    };

    auto extend_lift = [](AutonAction &action, Auton *p_auton){
        p_auton->lift_1->setTargetPosition((int) (LIFT_UP_POSITION * LIFT_TICKS_PER_CM));
        p_auton->lift_2->setTargetPosition((int) (LIFT_UP_POSITION * LIFT_TICKS_PER_CM));

        p_auton->lift_1->setPower(LIFT_UP_MLT);
        p_auton->lift_2->setPower(LIFT_UP_MLT);

        double lift_1_err = std::abs(LIFT_UP_POSITION - p_auton->lift_1->getCurrentPosition() / LIFT_TICKS_PER_CM);
        double lift_2_err = std::abs(LIFT_UP_POSITION - p_auton->lift_2->getCurrentPosition() / LIFT_TICKS_PER_CM);

        double lift_err = (lift_1_err + lift_2_err) / 2.0;

        p_auton->telemetry->addLine(utils::sprintf("lift_1_err = %.2f", lift_1_err));
        p_auton->telemetry->addLine(utils::sprintf("lift_2_err = %.2f", lift_2_err));
        p_auton->telemetry->addLine(utils::sprintf("lift_err = %.2f", lift_err));

        if (lift_err < 10.0) action.done = true;
    };

    auto retract_lift = [](AutonAction &action, Auton *p_auton){
        p_auton->basket_servo->setPosition(BASKET_SERVO_COLLECT);

        p_auton->lift_1->setTargetPosition(0);
        p_auton->lift_2->setTargetPosition(0);

        p_auton->lift_1->setPower(0.0);
        p_auton->lift_2->setPower(0.0);

        double lift_1_err = std::abs(p_auton->lift_1->getCurrentPosition() / LIFT_TICKS_PER_CM);
        double lift_2_err = std::abs(p_auton->lift_2->getCurrentPosition() / LIFT_TICKS_PER_CM);

        double lift_err = (lift_1_err + lift_2_err) / 2.0;

        p_auton->telemetry->addLine(utils::sprintf("lift_1_err = %.2f", lift_1_err));
        p_auton->telemetry->addLine(utils::sprintf("lift_2_err = %.2f", lift_2_err));
        p_auton->telemetry->addLine(utils::sprintf("lift_err = %.2f", lift_err));

        if (lift_err < 10.0) action.done = true;
    };

    time_point<high_resolution_clock> basket_reached_at;
    auto place_block = [&](AutonAction &action, Auton *p_auton){
        if (basket_reached_at == time_point<high_resolution_clock>())  {
            basket_reached_at = high_resolution_clock::now();
        }

        p_auton->lift_1->setTargetPosition((int) (LIFT_UP_POSITION * LIFT_TICKS_PER_CM));
        p_auton->lift_2->setTargetPosition((int) (LIFT_UP_POSITION * LIFT_TICKS_PER_CM));

        p_auton->lift_1->setPower(LIFT_HOLD_POWER);
        p_auton->lift_2->setPower(LIFT_HOLD_POWER);

        p_auton->basket_servo->setPosition(BASKET_SERVO_SCORE);

        duration<double> basket_delta = high_resolution_clock::now() - basket_reached_at;

        if (basket_delta.count() > 1.0) {
            action.done = true;
            basket_reached_at = high_resolution_clock::time_point();
        }
    };

    time_point<high_resolution_clock> block_timer;

    std::vector<AutonAction> actions = {
        {-1, [](AutonAction &action, Auton *p_auton){
            p_auton->lift_1->setTargetPosition(0);
            p_auton->lift_2->setTargetPosition(0);

            p_auton->lift_1->setMode(C_DcMotor::C_RunMode::STOP_AND_RESET_ENCODER);
            p_auton->lift_2->setMode(C_DcMotor::C_RunMode::STOP_AND_RESET_ENCODER);

            p_auton->lift_1->setMode(C_DcMotor::C_RunMode::RUN_TO_POSITION);
            p_auton->lift_2->setMode(C_DcMotor::C_RunMode::RUN_TO_POSITION);

            p_auton->extend_motor->setPower(1.0);

            p_auton->rotate_servo->setPosition(ROTATE_SERVO_MID);
            p_auton->basket_servo->setPosition(BASKET_SERVO_COLLECT);
        }, "init"},

        {1, extend_lift, "extend lift"},
        {2, place_block, "place block"},
        {3, retract_lift, "retract lift"},

        {5, [&](AutonAction &action, Auton *p_auton){
            if (block_timer == time_point<high_resolution_clock>())  {
                block_timer = high_resolution_clock::now();
            }

            p_auton->rotate_servo->setPosition(ROTATE_SERVO_DOWN);
            p_auton->pickup_servo->setPosition(PICKUP_SERVO_OPEN);
            duration<double> delta = high_resolution_clock::now() - block_timer;

            if (delta.count() > 1.0) {
                action.done = true;
                block_timer = high_resolution_clock::time_point();
            }
        }, "rotate to block"},

        {6, [&](AutonAction &action, Auton *p_auton){
            if (block_timer == time_point<high_resolution_clock>())  {
                block_timer = high_resolution_clock::now();
            }

            p_auton->pickup_servo->setPosition(PICKUP_SERVO_CLOSED);
            duration<double> delta = high_resolution_clock::now() - block_timer;

            if (delta.count() > 1.0) {
                action.done = true;
                block_timer = high_resolution_clock::time_point();
            }
        }, "pickup block"},

        {6, [&](AutonAction &action, Auton *p_auton){
            if (block_timer == time_point<high_resolution_clock>())  {
                block_timer = high_resolution_clock::now();
            }

            p_auton->rotate_servo->setPosition(ROTATE_SERVO_UP);
            duration<double> delta = high_resolution_clock::now() - block_timer;

            if (delta.count() > 1.0) {
                action.done = true;
                block_timer = high_resolution_clock::time_point();
            }
        }, "rotate to basket"},

        {6, [&](AutonAction &action, Auton *p_auton){
            if (block_timer == time_point<high_resolution_clock>())  {
                block_timer = high_resolution_clock::now();
            }

            p_auton->pickup_servo->setPosition(PICKUP_SERVO_OPEN);
            p_auton->rotate_servo->setPosition(ROTATE_SERVO_MID);
            duration<double> delta = high_resolution_clock::now() - block_timer;

            if (delta.count() > 1.0) {
                action.done = true;
                block_timer = high_resolution_clock::time_point();
            }
        }, "release block"},

        {7, extend_lift, "extend lift"},
        {8, place_block, "place block"},
        {9, retract_lift, "retract lift"},
    };

    PID pid_x = {1.0 / 20.0};
    PID pid_y = {1.0 / 20.0};
    PID pid_z = {1.0 / 20.0};

    (new Auton(p_jni, self, pid_x, pid_y, pid_z, path, actions))->runOpMode();
}