package org.firstinspires.ftc.teamcode;

public class Constants {
    public static final boolean PRACTICE_BOT = false;

    public static final double ODOMETRY_WHEEL_RADIUS = PRACTICE_BOT ? 4.5 : 3.0;
    public static final double ODOMETRY_TRACK_WIDTH = PRACTICE_BOT ? 45.0 : 17.0;
    public static final double ODOMETRY_PERP_OFFSET = PRACTICE_BOT ? (-45.0 / 2.0) : 12.5;

    public static final double ODOMETRY_TICKS_PER_CM = 8192.0 / (2 * Math.PI * ODOMETRY_WHEEL_RADIUS);

    public static final double DRIVETRAIN_FAST_MLT = 1.0;
    public static final double DRIVETRAIN_SLOW_MLT = 0.25;
    public static final double DRIVETRAIN_TURN_MLT = 0.75;

    public static final double EXTEND_MAX_DEGREES = 70.0;
    public static final double EXTEND_FORW_POWER = 1.0;
    public static final double EXTEND_BACK_POWER = 0.3;
    public static final double EXTEND_TICKS_PER_REV = 28.0 * 25.0;

    public static final double ROTATE_SERVO_UP = 0.85;
    public static final double ROTATE_SERVO_MID = 0.5;
    public static final double ROTATE_SERVO_DOWN = 0.03;

    public static final double PICKUP_SERVO_OPEN = 0.45;
    public static final double PICKUP_SERVO_CLOSED = 0.0;

    public static final double BASKET_SERVO_COLLECT = 0.5;
    public static final double BASKET_SERVO_SCORE = 0.1;
    public static final double BASKET_SERVO_BALANCE = 0.35;

    public static final double LIFT_HOLD_POWER = 0.2;
    public static final double LIFT_UP_MLT = 1.0;
    public static final double LIFT_DOWN_MLT = 0.75;

    public static final double LIFT_UP_POSITION = 50.0;
    public static final double LIFT_TICKS_PER_REV = 28.0 * 25.0;
    public static final double LIFT_GEAR_RADIUS = 2.0;
    public static final double LIFT_TICKS_PER_CM = LIFT_TICKS_PER_REV / (2 * Math.PI * LIFT_GEAR_RADIUS);

    public static final double AUTON_PID_X_THRESHOLD = 5.0;
    public static final double AUTON_PID_Y_THRESHOLD = 5.0;
    public static final double AUTON_PID_TH_THRESHOLD = 2.0;
}
