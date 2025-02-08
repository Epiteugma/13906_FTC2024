#pragma once
#include <robot.h>
#include <lib/c_op_mode.h>

class Drive : C_OpMode {
    using C_OpMode::C_OpMode;
    Robot *robot;

    double rotate_position;
    double pickup_position;
    double basket_position;

    int extend_target_position;
    double extend_power;
public:
    void runOpMode() override;

    void move_base();
    void collection();
    void placement();

    void extend_arm();
    void retract_arm();
};
