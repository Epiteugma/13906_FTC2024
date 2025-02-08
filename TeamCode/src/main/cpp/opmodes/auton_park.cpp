#include "auton.h"

extern "C"
JNIEXPORT void JNICALL Java_org_firstinspires_ftc_teamcode_opmodes_AutonPark_runOpMode(JNIEnv *p_jni, jobject self) {
    std::vector<double> path = {10.0, -100.0, 0.0};

    std::vector<AutonAction> actions = {
#ifndef PRACTICE_BOT // RUNS ONLY ON REAL BOT
        {-1, [](AutonAction &action, Auton *p_auton){
            p_auton->robot->lift_1->setTargetPosition(0);
            p_auton->robot->lift_2->setTargetPosition(0);

            p_auton->robot->lift_1->setMode(C_DcMotor::STOP_AND_RESET_ENCODER);
            p_auton->robot->lift_2->setMode(C_DcMotor::STOP_AND_RESET_ENCODER);

            p_auton->robot->lift_1->setMode(C_DcMotor::RUN_TO_POSITION);
            p_auton->robot->lift_2->setMode(C_DcMotor::RUN_TO_POSITION);

            p_auton->robot->extend_motor->setPower(1.0);

            p_auton->robot->rotate_servo->setPosition(ROTATE_SERVO_MID);
            p_auton->robot->basket_servo->setPosition(BASKET_SERVO_COLLECT);
        }, "init"}
#endif
    };

    auto pid_x = new PID(1.0 / 20.0, 0.0, 0.0);
    auto pid_y = new PID(1.0 / 20.0, 0.0, 0.0);
    auto pid_z = new PID(1.0 / 20.0, 0.0, 0.0);

    (new Auton(p_jni, self, pid_x, pid_y, pid_z, path, actions))->runOpMode();
}