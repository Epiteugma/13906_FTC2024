package org.firstinspires.ftc.teamcode.utils;

import com.qualcomm.robotcore.hardware.DcMotor;

import org.firstinspires.ftc.teamcode.utils.maths.Axis;
import org.firstinspires.ftc.teamcode.utils.maths.Vec3;

public class Odometry {
    public DcMotor leftEncoder;
    public DcMotor rightEncoder;
    public DcMotor perpEncoder;

    public double trackWidth;
    public double perpOffset;

    public boolean enableIntegrator = true;
    public Vec3 position = new Vec3(0, 0, 0);
    Vec3 lastEncoderValues = new Vec3(0, 0, 0);

    public Odometry(DcMotor leftEncoder, DcMotor rightEncoder, DcMotor perpEncoder, double trackWidth, double perpOffset) {
        this.leftEncoder = leftEncoder;
        this.rightEncoder = rightEncoder;
        this.perpEncoder = perpEncoder;

        this.trackWidth = trackWidth;
        this.perpOffset = perpOffset;
    }

    public void update() {
        Vec3 encoderValues = new Vec3(
                this.leftEncoder.getCurrentPosition(),
                this.rightEncoder.getCurrentPosition(),
                this.perpEncoder == null ? 0.0 : this.perpEncoder.getCurrentPosition()
        );

        Vec3 encoderDeltas = new Vec3(
                encoderValues.x - this.lastEncoderValues.x,
                encoderValues.y - this.lastEncoderValues.y,
                encoderValues.z - this.lastEncoderValues.z
        );

        this.lastEncoderValues.x = encoderValues.x;
        this.lastEncoderValues.y = encoderValues.y;
        this.lastEncoderValues.z = encoderValues.z;

        double phi = (encoderDeltas.y - encoderDeltas.x) / this.trackWidth;

        Vec3 deltas = new Vec3(
                encoderDeltas.z + this.perpOffset * phi,
                (encoderDeltas.x + encoderDeltas.y) / 2.0,
                phi
        );

        if (phi != 0.0 && this.enableIntegrator) {
            double oldX = deltas.x;
            double oldY = deltas.y;

            deltas.x = (Math.sin(phi) / phi) * oldX + ((Math.cos(phi) - 1) / phi) * oldY;
            deltas.y = ((-Math.cos(phi) + 1) / phi) * oldX + (Math.sin(phi) / phi) * oldY;
        }

        deltas.rotate(this.position.z, Axis.Z);

        this.position.x += deltas.x;
        this.position.y += deltas.y;
        this.position.z += deltas.z;
    }

    public void reset() {
        this.position = new Vec3(0, 0, 0);

        this.lastEncoderValues.x = this.leftEncoder.getCurrentPosition();
        this.lastEncoderValues.y = this.rightEncoder.getCurrentPosition();
        this.lastEncoderValues.z = this.perpEncoder == null ? 0.0 : this.perpEncoder.getCurrentPosition();
    }
}
