package org.firstinspires.ftc.teamcode;

import com.qualcomm.robotcore.eventloop.opmode.OpMode;
import com.qualcomm.robotcore.hardware.DcMotor;
import com.qualcomm.robotcore.hardware.DcMotorSimple;
import com.qualcomm.robotcore.hardware.Servo;

import org.firstinspires.ftc.teamcode.utils.Drivetrain;
import org.firstinspires.ftc.teamcode.utils.Odometry;

public class Robot {
    public Drivetrain drivetrain;
    public Odometry odometry;

    public DcMotor lift1;
    public DcMotor lift2;

    public DcMotor extendMotor;

    public Servo rotateServo;
    public Servo pickupServo;
    public Servo basketServo;

    public Robot(OpMode opMode) {
        this.drivetrain = new Drivetrain(
                opMode.hardwareMap.get(DcMotor.class, "front_left"),
                opMode.hardwareMap.get(DcMotor.class, "front_right"),
                opMode.hardwareMap.get(DcMotor.class, "back_left"),
                opMode.hardwareMap.get(DcMotor.class, "back_right")
        );

        if (Constants.PRACTICE_BOT) {
            this.drivetrain.frontLeft.setDirection(DcMotorSimple.Direction.REVERSE);
            this.drivetrain.frontRight.setDirection(DcMotorSimple.Direction.REVERSE);

            this.odometry = new Odometry(
                    opMode.hardwareMap.get(DcMotor.class, "left_encoder"),
                    opMode.hardwareMap.get(DcMotor.class, "right_encoder"),
                    opMode.hardwareMap.get(DcMotor.class, "perp_encoder"),
                    Constants.ODOMETRY_TRACK_WIDTH * Constants.ODOMETRY_TICKS_PER_CM,
                    Constants.ODOMETRY_PERP_OFFSET * Constants.ODOMETRY_TICKS_PER_CM
            );

            this.odometry.rightEncoder.setDirection(DcMotorSimple.Direction.REVERSE);
            this.odometry.perpEncoder.setDirection(DcMotorSimple.Direction.REVERSE);
        } else {
            this.drivetrain.frontLeft.setDirection(DcMotorSimple.Direction.REVERSE);
            this.drivetrain.frontRight.setDirection(DcMotorSimple.Direction.REVERSE);
            this.drivetrain.backRight.setDirection(DcMotorSimple.Direction.REVERSE);

            this.odometry = new Odometry(
                    this.drivetrain.backLeft,
                    opMode.hardwareMap.get(DcMotor.class, "right_encoder"),
                    this.drivetrain.frontLeft,
                    Constants.ODOMETRY_TRACK_WIDTH * Constants.ODOMETRY_TICKS_PER_CM,
                    Constants.ODOMETRY_PERP_OFFSET * Constants.ODOMETRY_TICKS_PER_CM
            );

            this.odometry.rightEncoder.setDirection(DcMotorSimple.Direction.REVERSE);

            this.lift1 = opMode.hardwareMap.get(DcMotor.class, "lift_1");
            this.lift2 = opMode.hardwareMap.get(DcMotor.class, "lift_2");

            this.lift2.setDirection(DcMotorSimple.Direction.REVERSE);

            this.extendMotor = opMode.hardwareMap.get(DcMotor.class, "extend");
            this.extendMotor.setDirection(DcMotorSimple.Direction.REVERSE);

            this.extendMotor.setTargetPosition((int) (Constants.EXTEND_MAX_DEGREES / -360.0 * Constants.EXTEND_TICKS_PER_REV));
            this.extendMotor.setMode(DcMotor.RunMode.STOP_AND_RESET_ENCODER);
            this.extendMotor.setMode(DcMotor.RunMode.RUN_TO_POSITION);

            this.rotateServo = opMode.hardwareMap.get(Servo.class, "rotate");
            this.pickupServo = opMode.hardwareMap.get(Servo.class, "pickup");
            this.basketServo = opMode.hardwareMap.get(Servo.class, "basket");
        }

        this.odometry.reset();
    }
}
