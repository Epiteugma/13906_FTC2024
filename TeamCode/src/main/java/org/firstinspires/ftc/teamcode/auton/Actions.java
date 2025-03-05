package org.firstinspires.ftc.teamcode.auton;

import com.qualcomm.robotcore.hardware.DcMotor;

import org.firstinspires.ftc.teamcode.Constants;

import java.util.Locale;

public class Actions {
    static long timer = 0;

    public static final AutonAction.ActionRuner init = (action, auton) -> {
        auton.robot.lift1.setTargetPosition(0);
        auton.robot.lift2.setTargetPosition(0);

        auton.robot.lift1.setMode(DcMotor.RunMode.STOP_AND_RESET_ENCODER);
        auton.robot.lift2.setMode(DcMotor.RunMode.STOP_AND_RESET_ENCODER);

        auton.robot.lift1.setMode(DcMotor.RunMode.RUN_TO_POSITION);
        auton.robot.lift2.setMode(DcMotor.RunMode.RUN_TO_POSITION);

        auton.robot.extendMotor.setTargetPosition((int) (Constants.EXTEND_MAX_DEGREES / -360.0 * Constants.EXTEND_TICKS_PER_REV));

        auton.robot.extendMotor.setMode(DcMotor.RunMode.STOP_AND_RESET_ENCODER);
        auton.robot.extendMotor.setMode(DcMotor.RunMode.RUN_TO_POSITION);

        auton.robot.extendMotor.setPower(1.0);

        auton.robot.rotateServo.setPosition(Constants.ROTATE_SERVO_MID);
        auton.robot.basketServo.setPosition(Constants.BASKET_SERVO_COLLECT);
    };

    public static final AutonAction.ActionRuner extendLift = (action, auton) -> {
        auton.robot.lift1.setTargetPosition((int) (Constants.LIFT_UP_POSITION * Constants.LIFT_TICKS_PER_CM));
        auton.robot.lift2.setTargetPosition((int) (Constants.LIFT_UP_POSITION * Constants.LIFT_TICKS_PER_CM));

        auton.robot.lift1.setMode(DcMotor.RunMode.RUN_TO_POSITION);
        auton.robot.lift2.setMode(DcMotor.RunMode.RUN_TO_POSITION);

        auton.robot.lift1.setPower(Constants.LIFT_UP_MLT);
        auton.robot.lift2.setPower(Constants.LIFT_UP_MLT);

        double lift1Err = Math.abs(Constants.LIFT_UP_POSITION - auton.robot.lift1.getCurrentPosition() / Constants.LIFT_TICKS_PER_CM);
        double lift2Err = Math.abs(Constants.LIFT_UP_POSITION - auton.robot.lift2.getCurrentPosition() / Constants.LIFT_TICKS_PER_CM);

        double liftErr = (lift1Err + lift2Err) / 2;

        auton.opMode.telemetry.addLine(String.format(Locale.getDefault(), "lift_1_err = %.2f", lift1Err));
        auton.opMode.telemetry.addLine(String.format(Locale.getDefault(), "lift_2_err = %.2f", lift2Err));
        auton.opMode.telemetry.addLine(String.format(Locale.getDefault(), "lift_err = %.2f", liftErr));

        if (liftErr < 10.0) action.done = true;
    };

    public static final AutonAction.ActionRuner retractLift = (action, auton) -> {
        auton.robot.lift1.setTargetPosition(0);
        auton.robot.lift2.setTargetPosition(0);

        auton.robot.lift1.setMode(DcMotor.RunMode.RUN_TO_POSITION);
        auton.robot.lift2.setMode(DcMotor.RunMode.RUN_TO_POSITION);

        auton.robot.lift1.setPower(-1);
        auton.robot.lift2.setPower(-1);

        auton.robot.basketServo.setPosition(Constants.BASKET_SERVO_COLLECT);

        double lift1Err = Math.abs(auton.robot.lift1.getCurrentPosition() / Constants.LIFT_TICKS_PER_CM);
        double lift2Err = Math.abs(auton.robot.lift2.getCurrentPosition() / Constants.LIFT_TICKS_PER_CM);

        double liftErr = (lift1Err + lift2Err) / 2;

        auton.opMode.telemetry.addLine(String.format(Locale.getDefault(), "lift_1_err = %.2f", lift1Err));
        auton.opMode.telemetry.addLine(String.format(Locale.getDefault(), "lift_2_err = %.2f", lift2Err));
        auton.opMode.telemetry.addLine(String.format(Locale.getDefault(), "lift_err = %.2f", liftErr));

        if (liftErr < 10.0) action.done = true;
    };

    public static final AutonAction.ActionRuner placeBlock = (action, auton) -> {
        if (timer == 0) timer = System.currentTimeMillis();

        auton.robot.lift1.setTargetPosition((int) (Constants.LIFT_UP_POSITION * Constants.LIFT_TICKS_PER_CM));
        auton.robot.lift2.setTargetPosition((int) (Constants.LIFT_UP_POSITION * Constants.LIFT_TICKS_PER_CM));

        auton.robot.lift1.setPower(Constants.LIFT_HOLD_POWER);
        auton.robot.lift2.setPower(Constants.LIFT_HOLD_POWER);

        auton.robot.basketServo.setPosition(Constants.BASKET_SERVO_SCORE);

        if (System.currentTimeMillis() - timer > 800) {
            timer = 0;
            action.done = true;
        }
    };

    public static final AutonAction.ActionRuner rotateToBlock = (action, auton) -> {
        if (timer == 0) timer = System.currentTimeMillis();

        auton.robot.rotateServo.setPosition(Constants.ROTATE_SERVO_DOWN);
        auton.robot.pickupServo.setPosition(Constants.PICKUP_SERVO_OPEN);

        if (System.currentTimeMillis() - timer > 1000) {
            timer = 0;
            action.done = true;
        }
    };

    public static final AutonAction.ActionRuner pickupBlock = (action, auton) -> {
        if (timer == 0) timer = System.currentTimeMillis();

        auton.robot.pickupServo.setPosition(Constants.PICKUP_SERVO_CLOSED);

        if (System.currentTimeMillis() - timer > 800) {
            timer = 0;
            action.done = true;
        }
    };

    public static final AutonAction.ActionRuner rotateToBasket = (action, auton) -> {
        if (timer == 0) timer = System.currentTimeMillis();

        auton.robot.rotateServo.setPosition(Constants.ROTATE_SERVO_UP);

        if (System.currentTimeMillis() - timer > 1000) {
            timer = 0;
            action.done = true;
        }
    };

    public static final AutonAction.ActionRuner releaseBlock = (action, auton) -> {
        auton.robot.pickupServo.setPosition(Constants.PICKUP_SERVO_OPEN);
        auton.robot.rotateServo.setPosition(Constants.ROTATE_SERVO_MID);
        action.done = true;
    };
}
