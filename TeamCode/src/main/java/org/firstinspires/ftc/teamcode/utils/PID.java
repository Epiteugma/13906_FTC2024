package org.firstinspires.ftc.teamcode.utils;

public class PID {
    public double kP = 1.0;
    public double kI = 0.0;
    public double kD = 0.0;

    double It = 0.0;
    double pError = 0.0;
    long last = System.nanoTime();

    public PID(double kP, double kI, double kD) {
        this.kP = kP;
        this.kI = kI;
        this.kD = kD;
    }

    public double update(double error) {
        double dt = (System.nanoTime() - last) / 1e9;

        double p = this.kP * error;
        double i = this.kI * error * dt;
        double d = dt == 0.0 ? 0.0 : this.kD * (error - this.pError) / dt;

        this.It += i;
        this.pError = error;

        return p + this.It + d;
    }

    public void reset() {
        this.It = 0.0;
        this.pError = 0.0;
        this.last = System.nanoTime();
    }
}
