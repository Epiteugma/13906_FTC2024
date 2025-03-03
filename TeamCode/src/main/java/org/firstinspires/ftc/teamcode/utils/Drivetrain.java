package org.firstinspires.ftc.teamcode.utils;

import com.qualcomm.robotcore.hardware.DcMotor;
import org.firstinspires.ftc.teamcode.utils.maths.Vec3;

public class Drivetrain {
    public DcMotor frontLeft;
    public DcMotor frontRight;
    public DcMotor backLeft;
    public DcMotor backRight;

    public double multiplier = 1.0;

    public Drivetrain(DcMotor frontLeft, DcMotor frontRight, DcMotor backLeft, DcMotor backRight) {
        this.frontLeft = frontLeft;
        this.frontRight = frontRight;
        this.backLeft = backLeft;
        this.backRight = backRight;
    }

    public void drive(double forwardPower, double strafePower, double turnPower) {
        double direction = Math.atan2(forwardPower, strafePower);
        double magnitude = Math.hypot(forwardPower, strafePower);

        magnitude *= this.multiplier;

        Vec3 powers = new Vec3(
                Math.cos(direction) * magnitude,
                Math.sin(direction) * magnitude,
                turnPower * this.multiplier
        );

        if (this.frontLeft != null) this.frontLeft.setPower(powers.y + powers.x + powers.z);
        if (this.frontRight != null) this.frontRight.setPower(powers.y - powers.x - powers.z);
        if (this.backLeft != null) this.backLeft.setPower(powers.y - powers.x + powers.z);
        if (this.backRight != null) this.backRight.setPower(powers.y + powers.x - powers.z);
    }
}
