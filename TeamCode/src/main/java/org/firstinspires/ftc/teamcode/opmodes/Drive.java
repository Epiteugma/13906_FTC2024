package org.firstinspires.ftc.teamcode.opmodes;

import com.qualcomm.robotcore.eventloop.opmode.LinearOpMode;
import com.qualcomm.robotcore.eventloop.opmode.TeleOp;
import com.qualcomm.robotcore.hardware.DcMotor;

import org.firstinspires.ftc.teamcode.Constants;
import org.firstinspires.ftc.teamcode.Robot;

@TeleOp(name = "[FTC24] Drive")
public class Drive extends LinearOpMode {
    Robot robot;

    double rotatePosition = Constants.ROTATE_SERVO_UP;
    double pickupPosition = Constants.PICKUP_SERVO_CLOSED;
    double basketPosition = Constants.BASKET_SERVO_COLLECT;
    int extendTargetPosition = 0;
    double extendPower = 0.0;

    @Override
    public void runOpMode() {
        this.robot = new Robot(this);

        this.waitForStart();
        this.retractArm();

        while (this.opModeIsActive()) {
            this.moveBase();

            if (!Constants.PRACTICE_BOT) {
                this.robot.rotateServo.setPosition(this.rotatePosition);
                this.robot.pickupServo.setPosition(this.pickupPosition);
                this.robot.basketServo.setPosition(this.basketPosition);

                this.robot.extendMotor.setTargetPosition(this.extendTargetPosition);
                this.robot.extendMotor.setPower(this.extendPower);

                this.collection();
                this.placement();
            }
        }
    }

    void moveBase() {
        this.robot.drivetrain.drive(
                -this.gamepad1.left_stick_y,
                this.gamepad1.left_stick_x,
                this.gamepad1.right_stick_x * Constants.DRIVETRAIN_TURN_MLT
        );

        if (this.gamepad1.right_bumper) this.robot.drivetrain.multiplier = Constants.DRIVETRAIN_FAST_MLT;
        else if (this.gamepad1.left_bumper) this.robot.drivetrain.multiplier = Constants.DRIVETRAIN_SLOW_MLT;
    }

    void collection() {
        if (this.gamepad2.dpad_up) {
            this.extendArm();
        } else if (this.gamepad2.dpad_down) {
            this.retractArm();

            this.rotatePosition = Constants.ROTATE_SERVO_UP;
            this.pickupPosition = Constants.PICKUP_SERVO_CLOSED;
        } else if (this.gamepad2.dpad_left) {
            this.rotatePosition = Constants.ROTATE_SERVO_MID;
        } else if (this.gamepad2.dpad_right) {
            this.rotatePosition = Constants.ROTATE_SERVO_DOWN;
        }

        if (this.gamepad2.y) {
            this.pickupPosition = Constants.PICKUP_SERVO_OPEN;
        } else if (this.gamepad2.a) {
            this.pickupPosition = Constants.PICKUP_SERVO_CLOSED;
        }
    }

    void placement() {
        double liftPower = -this.gamepad2.left_stick_y;

        if (liftPower == 0.0) {
            if (this.robot.lift1.getMode() != DcMotor.RunMode.RUN_TO_POSITION) this.robot.lift1.setTargetPosition(this.robot.lift1.getCurrentPosition());
            if (this.robot.lift2.getMode() != DcMotor.RunMode.RUN_TO_POSITION) this.robot.lift2.setTargetPosition(this.robot.lift2.getCurrentPosition());

            this.robot.lift1.setMode(DcMotor.RunMode.RUN_TO_POSITION);
            this.robot.lift1.setPower(Constants.LIFT_HOLD_POWER);

            this.robot.lift2.setMode(DcMotor.RunMode.RUN_TO_POSITION);
            this.robot.lift2.setPower(Constants.LIFT_HOLD_POWER);
        } else {
            liftPower *= liftPower > 0.0 ? Constants.LIFT_UP_MLT : Constants.LIFT_DOWN_MLT;

            this.robot.lift1.setMode(DcMotor.RunMode.RUN_WITHOUT_ENCODER);
            this.robot.lift1.setPower(liftPower);

            this.robot.lift2.setMode(DcMotor.RunMode.RUN_WITHOUT_ENCODER);
            this.robot.lift2.setPower(liftPower);
        }

        if (this.gamepad2.right_bumper) {
            this.basketPosition = Constants.BASKET_SERVO_SCORE;
        } else if (this.gamepad2.x) {
            this.basketPosition = Constants.BASKET_SERVO_BALANCE;
        } else if (this.gamepad2.left_bumper) {
            this.basketPosition = Constants.BASKET_SERVO_COLLECT;
        }
    }

    void extendArm() {
        this.extendTargetPosition = (int) (Constants.EXTEND_MAX_DEGREES / 360.0 * Constants.EXTEND_TICKS_PER_REV);
        this.extendPower = Constants.EXTEND_FORW_POWER;
    }

    void retractArm() {
        this.extendTargetPosition = (int) (Constants.EXTEND_MAX_DEGREES / -360.0 * Constants.EXTEND_TICKS_PER_REV);
        this.extendPower = Constants.EXTEND_BACK_POWER;
    }
}
