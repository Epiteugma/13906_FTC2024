package org.firstinspires.ftc.teamcode.auton;

import com.qualcomm.robotcore.eventloop.opmode.LinearOpMode;

import org.firstinspires.ftc.teamcode.Constants;
import org.firstinspires.ftc.teamcode.Robot;
import org.firstinspires.ftc.teamcode.utils.PID;
import org.firstinspires.ftc.teamcode.utils.maths.Axis;
import org.firstinspires.ftc.teamcode.utils.maths.Vec3;

import java.util.Locale;

public class Auton {
    LinearOpMode opMode;

    public Robot robot;
    Vec3 target = new Vec3(0, 0, 0);

    int nodeIndex = 0;
    int actionIndex = -1;
    Vec3 errors = new Vec3(0, 0, 0);
    Vec3 pidValues = new Vec3(0, 0, 0);

    public PID pidX = new PID(1, 0, 0);
    public PID pidY = new PID(1, 0, 0);
    public PID pidZ = new PID(1, 0, 0);

    Vec3[] path;
    AutonAction[] actions;

    public Auton(LinearOpMode opMode, Vec3[] path, AutonAction[] actions) {
        this.opMode = opMode;
        this.path = path;
        this.actions = actions;
    }

    public void runOpMode() {
        this.robot = new Robot(this.opMode);

        this.opMode.waitForStart();

        for (AutonAction action : this.actions) {
            if (action.atNode != -1) continue;
            action.run(this);
        }

        while (this.opMode.opModeIsActive()) {
            this.robot.odometry.update();
            this.printDebugInfo();

            this.target = this.path[this.nodeIndex];
            this.errors.x = this.target.x - this.robot.odometry.position.x / Constants.ODOMETRY_TICKS_PER_CM;
            this.errors.y = this.target.y - this.robot.odometry.position.y / Constants.ODOMETRY_TICKS_PER_CM;
            this.errors.z = this.target.z + this.robot.odometry.position.z / Math.PI * 180.0;

            this.pidValues.x = this.pidX.update(this.errors.x);
            this.pidValues.y = this.pidY.update(this.errors.y);
            this.pidValues.z = this.pidZ.update(this.errors.z);

            this.pidValues.rotate(-this.robot.odometry.position.z, Axis.Z);

            this.robot.drivetrain.drive(
                    this.pidValues.y,
                    this.pidValues.x,
                    this.pidValues.z
            );

            if (
                Math.abs(this.errors.x) < Constants.AUTON_PID_X_THRESHOLD &&
                Math.abs(this.errors.y) < Constants.AUTON_PID_Y_THRESHOLD &&
                Math.abs(this.errors.z) < Constants.AUTON_PID_TH_THRESHOLD
            ) {
                this.actionIndex = -1;

                for (int i = 0; i < this.actions.length; i++) {
                    AutonAction action = this.actions[i];
                    if (action.done || action.atNode != this.nodeIndex) continue;

                    action.run(this);

                    if (!action.done) {
                        this.actionIndex = i;
                        break;
                    }
                }

                if (this.actionIndex == -1) this.nodeIndex++;

                if (this.nodeIndex >= this.path.length) {
                    this.nodeIndex = this.path.length - 1;
                }
            }

            this.opMode.telemetry.update();
        }
    }

    void printDebugInfo() {
        this.opMode.telemetry.addLine(String.format(
                Locale.getDefault(),
                "(position) x = %.2f; y = %.2f; θ = %.2f",
                this.robot.odometry.position.x / Constants.ODOMETRY_TICKS_PER_CM,
                this.robot.odometry.position.y / Constants.ODOMETRY_TICKS_PER_CM,
                this.robot.odometry.position.z / Math.PI * 180.0
        ));

        this.opMode.telemetry.addLine(String.format(
                Locale.getDefault(),
                "(target) x = %.2f; y = %.2f; θ = %.2f",
                this.target.x,
                this.target.y,
                this.target.z
        ));

        this.opMode.telemetry.addLine();

        this.opMode.telemetry.addLine(String.format(Locale.getDefault(), "forward_power = %.2f", this.pidValues.y));
        this.opMode.telemetry.addLine(String.format(Locale.getDefault(), "strafe_power = %.2f", this.pidValues.x));
        this.opMode.telemetry.addLine(String.format(Locale.getDefault(), "turn_power = %.2f", this.pidValues.z));

        this.opMode.telemetry.addLine();
        this.opMode.telemetry.addLine(String.format(Locale.getDefault(), "node_index = %d", this.nodeIndex));

        if (this.actionIndex != -1) {
            String name = this.actions[this.actionIndex].name;
            if (name.isEmpty()) name = "< unnamed >";

            this.opMode.telemetry.addLine(String.format(Locale.getDefault(), "current action = %s", name));
        } else {
            this.opMode.telemetry.addLine("current action = < none >");
        }

        this.opMode.telemetry.addLine();
    }
}
