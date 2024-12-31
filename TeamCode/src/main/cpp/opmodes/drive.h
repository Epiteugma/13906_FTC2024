#include "../lib/c_op_mode.h"
#include "../utils/kinematics/drivetrain.h"

class Drive : C_OpMode {
    using C_OpMode::C_OpMode;

    Drivetrain drivetrain{};

    C_DcMotor *lift_1;
    C_DcMotor *lift_2;

    C_DcMotor *extend_motor;

    C_Servo *rotate_servo;
    C_Servo *pickup_servo;
    C_Servo *basket_servo;
public:
    void runOpMode() override;
};