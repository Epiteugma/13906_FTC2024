package org.firstinspires.ftc.teamcode.opmodes;

import com.qualcomm.robotcore.eventloop.opmode.Autonomous;
import com.qualcomm.robotcore.eventloop.opmode.LinearOpMode;

import org.firstinspires.ftc.teamcode.Constants;
import org.firstinspires.ftc.teamcode.auton.Actions;
import org.firstinspires.ftc.teamcode.auton.Auton;
import org.firstinspires.ftc.teamcode.auton.AutonAction;
import org.firstinspires.ftc.teamcode.utils.PID;
import org.firstinspires.ftc.teamcode.utils.maths.Vec3;

@Autonomous(name = "[FTC24] Park")
public class AutonPark extends LinearOpMode {

    @Override
    public void runOpMode() {
        if (Constants.PRACTICE_BOT) return; // ONLY RUN AUTON ON REAL BOT

        Vec3[] path = new Vec3[]{
                new Vec3(10, -100, 0)
        };

        AutonAction[] actions = new AutonAction[]{
                new AutonAction(-1, Actions.init)
        };

        Auton auton = new Auton(this, path, actions);

        auton.pidX = new PID(1 / 20.0, 0, 0);
        auton.pidY = new PID(1 / 20.0, 0, 0);
        auton.pidZ = new PID(1 / 15.0, 0, 0);

        auton.runOpMode();
    }

}
