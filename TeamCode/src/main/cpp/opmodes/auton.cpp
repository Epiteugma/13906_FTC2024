#include "auton.h"

Auton::Auton(
    JNIEnv *p_jni, jobject self,
    PID *pid_x, PID *pid_y, PID *pid_z,
    std::vector<double> path,
    std::vector<AutonAction> actions
) : C_OpMode(p_jni, self) {
    this->pid_x = pid_x;
    this->pid_y = pid_y;
    this->pid_z = pid_z;

    this->path = std::move(path);
    this->actions = std::move(actions);

    this->node_index = 0;
    this->action_index = -1;

    this->robot = nullptr;
}

void Auton::runOpMode() {
    this->robot = new Robot(this);

    this->waitForStart();

    for (auto &action : this->actions) {
        if (action.at_node != -1) continue;
        action.run(action, this);
    }

    auto last = std::chrono::high_resolution_clock::now();

    while (this->opModeIsActive()) {
        auto now = std::chrono::high_resolution_clock::now();
        auto delta = now - last;
        last = now;

        this->robot->odometry->update();
        this->printDebugInfo();

        this->target[0] = this->path[this->node_index * 3];
        this->target[1] = this->path[this->node_index * 3 + 1];
        this->target[2] = this->path[this->node_index * 3 + 2];

        double theta = this->robot->odometry->position[2];

        maths::vec3 errors{
            this->target[0] - (this->robot->odometry->position[0] / ODOMETRY_TICKS_PER_CM),
            this->target[1] - (this->robot->odometry->position[1] / ODOMETRY_TICKS_PER_CM),
            this->target[2] + (theta / M_PI * 180.0)
        };

        this->pid_values[0] = this->pid_x->update(errors[0], delta);
        this->pid_values[1] = this->pid_y->update(errors[1], delta);
        this->pid_values[2] = this->pid_z->update(errors[2], delta);

        maths::vec2 rotated_pid_values{
            std::cos(-theta) * this->pid_values[0] - std::sin(-theta) * this->pid_values[1],
            std::sin(-theta) * this->pid_values[0] + std::cos(-theta) * this->pid_values[1]
        };

        this->pid_values[0] = rotated_pid_values[0];
        this->pid_values[1] = rotated_pid_values[1];

        this->robot->drivetrain->drive(maths::vec3{
            this->pid_values[1], // forward
            this->pid_values[2], // turn
            this->pid_values[0], // strafe
        });

        if (
            std::abs(errors[0]) < AUTON_PID_X_THRESHOLD &&
            std::abs(errors[1]) < AUTON_PID_Y_THRESHOLD &&
            std::abs(errors[2]) < AUTON_PID_TH_THRESHOLD
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

            if (this->action_index == -1) this->node_index++;

            if (node_index >= this->path.size() / 3) {
                node_index = (int) ((this->path.size() / 3) - 1);
            }
        }

        this->telemetry->update();
    }
}

void Auton::printDebugInfo() {
    this->telemetry->addLine(utils::sprintf(
            "(position) x = %.2f; y = %.2f; θ = %.2f",
            this->robot->odometry->position[0] / ODOMETRY_TICKS_PER_CM,
            this->robot->odometry->position[1] / ODOMETRY_TICKS_PER_CM,
            this->robot->odometry->position[2] / M_PI * 180.0
    ));

    this->telemetry->addLine(utils::sprintf(
            "(target) x = %.2f; y = %.2f; θ = %.2f",
            this->path[this->node_index * 3],
            this->path[this->node_index * 3 + 1],
            this->path[this->node_index * 3 + 2]
    ));

    this->telemetry->addLine();
    this->telemetry->addLine(utils::sprintf("forward_power = %.2f", this->pid_values[1]));
    this->telemetry->addLine(utils::sprintf("strafe_power = %.2f", this->pid_values[0]));
    this->telemetry->addLine(utils::sprintf("turn_power = %.2f", this->pid_values[2]));

#ifndef PRACTICE_BOT
    this->telemetry->addLine();
    this->telemetry->addLine(utils::sprintf("lift_1 power = %.2f", this->robot->lift_1->getPower()));
    this->telemetry->addLine(utils::sprintf("lift_2 power = %.2f", this->robot->lift_2->getPower()));
#endif

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