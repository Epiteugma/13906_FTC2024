#include "auton.h"



extern "C"
JNIEXPORT void JNICALL Java_org_firstinspires_ftc_teamcode_opmodes_AutonPark_runOpMode(JNIEnv *p_jni, jobject self) {
    std::vector<math::vec3> path = {
        {10.0, -100.0, 0.0}
    };

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
    };

    PID pid_x = {1.0 / 20.0};
    PID pid_y = {1.0 / 20.0};
    PID pid_z = {1.0 / 20.0};

    (new Auton(p_jni, self, pid_x, pid_y, pid_z, path, actions))->runOpMode();
}