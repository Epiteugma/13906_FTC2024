package org.firstinspires.ftc.teamcode.utils.maths;

public class Vec3 {
    public double x;
    public double y;
    public double z;

    public Vec3(double x, double y, double z) {
        this.x = x;
        this.y = y;
        this.z = z;
    }

    public Vec3 rotate(double theta, Axis axis) {
        double oldX;
        double oldY;
        double oldZ;

        switch (axis) {
            case X:
                oldY = this.y;
                oldZ = this.z;

                this.y = Math.cos(theta) * oldY - Math.sin(theta) * oldZ;
                this.z = Math.sin(theta) * oldY + Math.cos(theta) * oldZ;
                break;
            case Y:
                oldX = this.x;
                oldZ = this.z;

                this.x = Math.cos(theta) * oldX - Math.sin(theta) * oldZ;
                this.z = Math.sin(theta) * oldX + Math.cos(theta) * oldZ;
                break;
            case Z:
                oldX = this.x;
                oldY = this.y;

                this.x = Math.cos(theta) * oldX - Math.sin(theta) * oldY;
                this.y = Math.sin(theta) * oldX + Math.cos(theta) * oldY;
                break;
        }

        return this;
    }
}
