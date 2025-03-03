package org.firstinspires.ftc.teamcode.utils.maths;

public class Vec2 {
    public double x;
    public double y;

    public Vec2(double x, double y) {
        this.x = x;
        this.y = y;
    }

    public Vec2 rotate(double theta) {
        double oldX = this.x;
        double oldY = this.y;

        this.x = Math.cos(theta) * oldX - Math.sin(theta) * oldY;
        this.y = Math.sin(theta) * oldX + Math.cos(theta) * oldY;

        return this;
    }
}
