#pragma once
#include "vector"

#include "../lib/c_op_mode.h"
#include "../utils/kinematics/drivetrain.h"
#include "../utils/control/pid.h"
#include "../utils/odometry/odometry.h"
#include "../utils/utils.h"
#include "../utils/constants.h"
#include "../profiles/profiles.h"

struct AutonAction;

class Auton : public C_OpMode {
    PID pid_x;
    PID pid_y;
    PID pid_z;
    math::vec3 pid_values;

    std::vector<math::vec3> path;
    std::vector<AutonAction> actions;

    void printDebugInfo();
    void init();
public:
    Auton(
        JNIEnv *p_jni, jobject self,
        PID pid_x, PID pid_y, PID pid_z,
        std::vector<math::vec3> path,
        std::vector<AutonAction> actions
    );

    int node_index;
    int action_index;
    math::vec3 target;

    Odometry odometry{};
    Drivetrain drivetrain{};

    C_DcMotor *lift_1;
    C_DcMotor *lift_2;

    C_DcMotor *extend_motor;

    C_Servo *rotate_servo;
    C_Servo *pickup_servo;
    C_Servo *basket_servo;

    void runOpMode() override;
};

struct AutonAction {
    int at_node;
    std::function<void(AutonAction &action, Auton *p_auton)> run;

    const char* name;
    bool done;
};
