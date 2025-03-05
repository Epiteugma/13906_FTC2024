package org.firstinspires.ftc.teamcode.opmodes;

import com.qualcomm.robotcore.eventloop.opmode.Autonomous;
import com.qualcomm.robotcore.eventloop.opmode.LinearOpMode;

import org.firstinspires.ftc.teamcode.Constants;
import org.firstinspires.ftc.teamcode.auton.Actions;
import org.firstinspires.ftc.teamcode.auton.Auton;
import org.firstinspires.ftc.teamcode.auton.AutonAction;
import org.firstinspires.ftc.teamcode.utils.PID;
import org.firstinspires.ftc.teamcode.utils.maths.Vec3;

@Autonomous(name = "[FTC24] Place Red")
public class AutonPlaceRed extends LinearOpMode {

    @Override
    public void runOpMode() {
        if (Constants.PRACTICE_BOT) return; // ONLY RUN AUTON ON REAL BOT

        Vec3[] path = new Vec3[]{
                new Vec3(-7, 0, 0),
                new Vec3(-15, -57, 0),
                new Vec3(-15, -57, -40),
                new Vec3(-8, -68, -40), // score block 2
                new Vec3(-20, -50, -40),
                new Vec3(-20, -50, -180),
                new Vec3(-20, -8, -180),
                new Vec3(-82, -7, -180),
                new Vec3(-82, -19, -180),
                new Vec3(-30, -60, -180),
                new Vec3(-30, -60, -45),
                new Vec3(-7, -70, -45), // score block 2
                new Vec3(-40, -60, -45),
                new Vec3(-40, -60, -175),
                new Vec3(-40, -25, -175),
                new Vec3(-80, -25, -175),
                new Vec3(-80, -36, -175),
                new Vec3(-35, -36, -175),
                new Vec3(-35, -52, -35),
                new Vec3(-12, -75, -35), // score block 3
                new Vec3(-40, -60, -35),
        };

        AutonAction[] actions = new AutonAction[]{
                new AutonAction(-1, Actions.init),
                new AutonAction(2, Actions.extendLift, "extend lift"),
                new AutonAction(3, Actions.placeBlock, "place block"),
                new AutonAction(4, Actions.retractLift, "retract lift"),
                new AutonAction(7, Actions.rotateToBlock, "rotate to block"),
                new AutonAction(8, Actions.pickupBlock, "pickup block"),
                new AutonAction(8, Actions.rotateToBasket, "rotate to basket"),
                new AutonAction(8, Actions.releaseBlock, "release block"),
                new AutonAction(10, Actions.extendLift, "extend lift"),
                new AutonAction(11, Actions.placeBlock, "place block"),
                new AutonAction(12, Actions.retractLift, "retract lift"),
                new AutonAction(15, Actions.rotateToBlock, "rotate to block"),
                new AutonAction(16, Actions.pickupBlock, "pickup block"),
                new AutonAction(16, Actions.rotateToBasket, "rotate to basket"),
                new AutonAction(16, Actions.releaseBlock, "release block"),
                new AutonAction(18, Actions.extendLift, "extend lift"),
                new AutonAction(19, Actions.placeBlock, "place block"),
                new AutonAction(20, Actions.retractLift, "retract lift"),
        };

        Auton auton = new Auton(this, path, actions);

        auton.pidX = new PID(1 / 20.0, 0, 0);
        auton.pidY = new PID(1 / 20.0, 0, 0);
        auton.pidZ = new PID(1 / 15.0, 0, 0);

        auton.runOpMode();
    }

}
