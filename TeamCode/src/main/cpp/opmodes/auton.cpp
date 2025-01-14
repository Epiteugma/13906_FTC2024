#include "auton.h"

#include <utility>

Auton::Auton(
    JNIEnv *p_jni, jobject self,
    PID pid_x, PID pid_y, PID pid_z,
    std::vector<math::vec3> path,
    std::vector<AutonAction> actions
) : C_OpMode(p_jni, self) {
    this->pid_x = pid_x;
    this->pid_y = pid_y;
    this->pid_z = pid_z;

    this->path = std::move(path);
    this->actions = std::move(actions);

    this->node_index = 0;
    this->action_index = -1;
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

    this->rotate_servo = this->hardwareMap->getServo("rotate");
    this->pickup_servo = this->hardwareMap->getServo("pickup");
    this->basket_servo = this->hardwareMap->getServo("basket");

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
    this->init();

    this->waitForStart();
    this->odometry.init();

    for (auto &action : this->actions) {
        if (action.at_node != -1) continue;
        action.run(action, this);
    }

    while (this->opModeIsActive()) {
        this->odometry.update();
        this->printDebugInfo();
        this->target = this->path[this->node_index];

        this->pid_values = {
            this->pid_x.update(this->target.x, this->odometry.pos.x / ODOMETRY_TICKS_PER_CM),
            this->pid_y.update(this->target.y, this->odometry.pos.y / ODOMETRY_TICKS_PER_CM),
            this->pid_z.update(this->target.z, -this->odometry.theta / M_PI * 180.0),
        };

        math::vec2 xy = this->pid_values.xy();
        xy.rotate(-this->odometry.theta);

        this->pid_values.x = xy.x;
        this->pid_values.y = xy.y;

        this->drivetrain.drive(
            this->pid_values.y,
            this->pid_values.x,
            this->pid_values.z
        );

        double turn_err = std::abs(this->target.z + this->odometry.theta / M_PI * 180);
        double x_err = std::abs(this->target.x - (this->odometry.pos.x / ODOMETRY_TICKS_PER_CM));
        double y_err = std::abs(this->target.y - (this->odometry.pos.y / ODOMETRY_TICKS_PER_CM));

        if (
            turn_err < AUTON_PID_TH_THRESHOLD &&
            x_err    < AUTON_PID_X_THRESHOLD &&
            y_err    < AUTON_PID_Y_THRESHOLD
        ) {
            this->action_index = -1;

            for (int i = 0; i < this->actions.size(); i++) {
                auto &action = this->actions[i];

                if (action.done || action.at_node != this->node_index) {
                    continue;
                }

                action.run(action, this);

                if (!action.done) {
                    this->action_index = i;
                    break;
                }
            }

            if (action_index == -1) node_index++;

            if (node_index >= this->path.size()) {
                node_index = (int) (this->path.size() - 1);
            }
        }

        this->telemetry->update();
    }
}

void Auton::printDebugInfo() {
    this->telemetry->addLine(utils::sprintf(
        "(position) x = %.2f; y = %.2f; θ = %.2f",
        odometry.pos.x / ODOMETRY_TICKS_PER_CM,
        odometry.pos.y / ODOMETRY_TICKS_PER_CM,
        odometry.theta / M_PI * 180.0
    ));

    this->telemetry->addLine(utils::sprintf(
        "(velocity) x = %.2f; y = %.2f",
        odometry.velocity.x / (ODOMETRY_TICKS_PER_CM * 100.0), // ms-1
        odometry.velocity.y / (ODOMETRY_TICKS_PER_CM * 100.0)
    ));

    this->telemetry->addLine();
    this->telemetry->addLine(utils::sprintf("forward_power = %.2f", this->pid_values.x));
    this->telemetry->addLine(utils::sprintf("strafe_power = %.2f", this->pid_values.y));
    this->telemetry->addLine(utils::sprintf("turn_power = %.2f", this->pid_values.z));

    this->telemetry->addLine();
    this->telemetry->addLine(utils::sprintf("lift_1 power = %.2f", this->lift_1->getPower()));
    this->telemetry->addLine(utils::sprintf("lift_2 power = %.2f", this->lift_2->getPower()));

    this->telemetry->addLine();
    this->telemetry->addLine(utils::sprintf("node index = %d", this->node_index));

    if (this->action_index != -1) {
        auto name = this->actions[this->action_index].name;
        if (name == nullptr || strlen(name) == 0) name = "< unnamed >";

        this->telemetry->addLine(utils::sprintf("current action = %s", name));
    } else {
        this->telemetry->addLine("current action = < none >");
    }

    this->telemetry->addLine();
}
