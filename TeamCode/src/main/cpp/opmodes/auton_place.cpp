#include "auton.h"

extern "C"
JNIEXPORT void JNICALL Java_org_firstinspires_ftc_teamcode_opmodes_AutonPlace_runOpMode(JNIEnv *p_jni, jobject self) {
    std::vector<double> path = {
        -30.0, -60.0, 0.0,
        -30.0, -60.0, -45.0,
        -10.0, -70.0, -45.0,
        -20.0, -50.0, -45.0,
        -20.0, -50.0, -180.0,
        -30.0, -5.0, -180.0,
        -83.0, -5.0, -180.0,
        -83.0, -18.0, -180.0,
        -83.0, -18.0, -45.0,
        -30.0, -65.0, -45.0,
        -0.0, -65.0, -45.0,
        -0.0, -40.0, -45.0,
    };

#ifndef PRACTICE_BOT
    std::chrono::time_point<std::chrono::high_resolution_clock> timer;

    auto extend_lift = [](AutonAction &action, Auton *p_auton){
        p_auton->robot->lift_1->setTargetPosition((int) (LIFT_UP_POSITION * LIFT_TICKS_PER_CM));
        p_auton->robot->lift_2->setTargetPosition((int) (LIFT_UP_POSITION * LIFT_TICKS_PER_CM));

        p_auton->robot->lift_1->setMode(C_DcMotor::C_RunMode::RUN_TO_POSITION);
        p_auton->robot->lift_2->setMode(C_DcMotor::C_RunMode::RUN_TO_POSITION);

        p_auton->robot->lift_1->setPower(LIFT_UP_MLT);
        p_auton->robot->lift_2->setPower(LIFT_UP_MLT);

        double lift_1_err = std::abs(LIFT_UP_POSITION - p_auton->robot->lift_1->getCurrentPosition() / LIFT_TICKS_PER_CM);
        double lift_2_err = std::abs(LIFT_UP_POSITION - p_auton->robot->lift_2->getCurrentPosition() / LIFT_TICKS_PER_CM);

        double lift_err = (lift_1_err + lift_2_err) / 2.0;

        p_auton->telemetry->addLine(utils::sprintf("lift_1_err = %.2f", lift_1_err));
        p_auton->telemetry->addLine(utils::sprintf("lift_2_err = %.2f", lift_2_err));
        p_auton->telemetry->addLine(utils::sprintf("lift_err = %.2f", lift_err));

        if (lift_err < 10.0) action.done = true;
    };

    auto retract_lift = [](AutonAction &action, Auton *p_auton){
        p_auton->robot->basket_servo->setPosition(BASKET_SERVO_COLLECT);

        p_auton->robot->lift_1->setTargetPosition(0);
        p_auton->robot->lift_2->setTargetPosition(0);

        p_auton->robot->lift_1->setMode(C_DcMotor::C_RunMode::RUN_WITHOUT_ENCODER);
        p_auton->robot->lift_2->setMode(C_DcMotor::C_RunMode::RUN_WITHOUT_ENCODER);

        p_auton->robot->lift_1->setPower(-1.0);
        p_auton->robot->lift_2->setPower(-1.0);

        double lift_1_err = std::abs(p_auton->robot->lift_1->getCurrentPosition() / LIFT_TICKS_PER_CM);
        double lift_2_err = std::abs(p_auton->robot->lift_2->getCurrentPosition() / LIFT_TICKS_PER_CM);

        double lift_err = (lift_1_err + lift_2_err) / 2.0;

        p_auton->telemetry->addLine(utils::sprintf("lift_1_err = %.2f", lift_1_err));
        p_auton->telemetry->addLine(utils::sprintf("lift_2_err = %.2f", lift_2_err));
        p_auton->telemetry->addLine(utils::sprintf("lift_err = %.2f", lift_err));

        if (lift_err < 10.0) action.done = true;
    };

    auto place_block = [&](AutonAction &action, Auton *p_auton){
        if (timer == std::chrono::time_point<std::chrono::high_resolution_clock>())  {
            timer = std::chrono::high_resolution_clock::now();
        }

        p_auton->robot->lift_1->setTargetPosition((int) (LIFT_UP_POSITION * LIFT_TICKS_PER_CM));
        p_auton->robot->lift_2->setTargetPosition((int) (LIFT_UP_POSITION * LIFT_TICKS_PER_CM));

        p_auton->robot->lift_1->setPower(LIFT_HOLD_POWER);
        p_auton->robot->lift_2->setPower(LIFT_HOLD_POWER);

        p_auton->robot->basket_servo->setPosition(BASKET_SERVO_SCORE);

        std::chrono::duration<double> basket_delta = std::chrono::high_resolution_clock::now() - timer;

        if (basket_delta.count() > 1.0) {
            action.done = true;
            timer = std::chrono::high_resolution_clock::time_point();
        }
    };

    auto rotate_to_block = [&](AutonAction &action, Auton *p_auton){
        if (timer == std::chrono::time_point<std::chrono::high_resolution_clock>())  {
            timer = std::chrono::high_resolution_clock::now();
        }

        p_auton->robot->rotate_servo->setPosition(ROTATE_SERVO_DOWN);
        p_auton->robot->pickup_servo->setPosition(PICKUP_SERVO_OPEN);
        std::chrono::duration<double> delta = std::chrono::high_resolution_clock::now() - timer;

        if (delta.count() > 1.0) {
            action.done = true;
            timer = std::chrono::high_resolution_clock::time_point();
        }
    };

    auto pickup_block = [&](AutonAction &action, Auton *p_auton){
        if (timer == std::chrono::time_point<std::chrono::high_resolution_clock>())  {
            timer = std::chrono::high_resolution_clock::now();
        }

        p_auton->robot->pickup_servo->setPosition(PICKUP_SERVO_CLOSED);
        std::chrono::duration<double> delta = std::chrono::high_resolution_clock::now() - timer;

        if (delta.count() > 1.0) {
            action.done = true;
            timer = std::chrono::high_resolution_clock::time_point();
        }
    };

    auto rotate_to_basket = [&](AutonAction &action, Auton *p_auton){
        if (timer == std::chrono::time_point<std::chrono::high_resolution_clock>())  {
            timer = std::chrono::high_resolution_clock::now();
        }

        p_auton->robot->rotate_servo->setPosition(ROTATE_SERVO_UP);
        std::chrono::duration<double> delta = std::chrono::high_resolution_clock::now() - timer;

        if (delta.count() > 1.0) {
            action.done = true;
            timer = std::chrono::high_resolution_clock::time_point();
        }
    };

    auto release_block = [&](AutonAction &action, Auton *p_auton){
        p_auton->robot->pickup_servo->setPosition(PICKUP_SERVO_OPEN);
        p_auton->robot->rotate_servo->setPosition(ROTATE_SERVO_MID);
        action.done = true;
    };
#endif

    std::vector<AutonAction> actions = {
#ifndef PRACTICE_BOT // ONLY RUNS ON REAL BOT
        {-1, [](AutonAction &action, Auton *p_auton){
            p_auton->robot->lift_1->setTargetPosition(0);
            p_auton->robot->lift_2->setTargetPosition(0);

            p_auton->robot->lift_1->setMode(C_DcMotor::C_RunMode::STOP_AND_RESET_ENCODER);
            p_auton->robot->lift_2->setMode(C_DcMotor::C_RunMode::STOP_AND_RESET_ENCODER);

            p_auton->robot->lift_1->setMode(C_DcMotor::C_RunMode::RUN_TO_POSITION);
            p_auton->robot->lift_2->setMode(C_DcMotor::C_RunMode::RUN_TO_POSITION);

            p_auton->robot->extend_motor->setTargetPosition(EXTEND_MAX_DEGREES / -360.0 * EXTEND_TICKS_PER_REV);

            p_auton->robot->extend_motor->setMode(C_DcMotor::STOP_AND_RESET_ENCODER);
            p_auton->robot->extend_motor->setMode(C_DcMotor::RUN_TO_POSITION);

            p_auton->robot->extend_motor->setPower(1.0);

            p_auton->robot->rotate_servo->setPosition(ROTATE_SERVO_MID);
            p_auton->robot->basket_servo->setPosition(BASKET_SERVO_COLLECT);
        }, "init"},

        {1, extend_lift, "extend lift"},
        {2, place_block, "place block"},
        {3, retract_lift, "retract lift"},
        {6, rotate_to_block, "rtb"},
        {7, pickup_block, "pb"},
        {7, rotate_to_basket, "rtb"},
        {7, release_block, "rb"},
        {9, extend_lift, "extend"},
        {10, place_block, "place"},
        {11, retract_lift, "rb"},
#endif
    };

    auto pid_x = new PID(1.0 / 20.0, 0.0, 0.0);
    auto pid_y = new PID(1.0 / 20.0, 0.0, 0.0);
    auto pid_z = new PID(1.0 / 20.0, 0.0, 0.0);

    (new Auton(p_jni, self, pid_x, pid_y, pid_z, path, actions))->runOpMode();
}