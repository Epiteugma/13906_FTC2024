#pragma once
#include <robot.h>
#include <constants.h>
#include <utils/utils.h>
#include <utils/control/pid.h>
#include <lib/c_op_mode.h>

struct AutonAction;

class Auton : public C_OpMode {
    PID *pid_x;
    PID *pid_y;
    PID *pid_z;
    maths::vec3 pid_values;

    std::vector<double> path;
    std::vector<AutonAction> actions;

    int node_index;
    int action_index;

    maths::vec3 target;

    void printDebugInfo();
public:
    Auton(
        JNIEnv *p_jni, jobject self,
        PID *pid_x, PID *pid_y, PID *pid_z,
        std::vector<double> path,
        std::vector<AutonAction> actions
    );

    Robot *robot;
    void runOpMode() override;
};

struct AutonAction {
    int at_node;
    std::function<void(AutonAction &action, Auton *p_auton)> run;

    const char* name;
    bool done;
};