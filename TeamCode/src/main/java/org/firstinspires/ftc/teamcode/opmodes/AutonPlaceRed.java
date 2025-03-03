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
                new Vec3(-35, -57, 0),
                new Vec3(-35, -57, -50),
                new Vec3(-9, -70, -50), // score block 2
                new Vec3(-20, -50, -50),
                new Vec3(-20, -50, -180),
                new Vec3(-20, -7, -180),
                new Vec3(-85, -4, -180),
                new Vec3(-85, -18, -180),
                new Vec3(-30, -60, -180),
                new Vec3(-30, -60, -45),
                new Vec3(-7, -70, -45), // score block 2
                new Vec3(-40, -60, -45),
                new Vec3(-40, -60, -180),
                new Vec3(-40, -4, -180),
                new Vec3(-80.5, -4, -180),
                new Vec3(-80, -35, -180),
                new Vec3(-35, -36, -180),
                new Vec3(-35, -52, -45),
                new Vec3(-13, -80, -45),
                new Vec3(-40, -60, -45),
        };

        AutonAction[] actions = new AutonAction[]{
                new AutonAction(-1, Actions.init),
                new AutonAction(1, Actions.extendLift, "extend lift"),
                new AutonAction(2, Actions.placeBlock, "place block"),
                new AutonAction(3, Actions.retractLift, "retract lift"),
                new AutonAction(6, Actions.rotateToBlock, "rotate to block"),
                new AutonAction(7, Actions.pickupBlock, "pickup block"),
                new AutonAction(7, Actions.rotateToBasket, "rotate to basket"),
                new AutonAction(7, Actions.releaseBlock, "release block"),
                new AutonAction(9, Actions.extendLift, "extend lift"),
                new AutonAction(10, Actions.placeBlock, "place block"),
                new AutonAction(11, Actions.retractLift, "retract lift"),
                new AutonAction(14, Actions.rotateToBlock, "rotate to block"),
                new AutonAction(15, Actions.pickupBlock, "pickup block"),
                new AutonAction(15, Actions.rotateToBasket, "rotate to basket"),
                new AutonAction(15, Actions.releaseBlock, "release block"),
                new AutonAction(17, Actions.extendLift, "extend lift"),
                new AutonAction(18, Actions.placeBlock, "place block"),
                new AutonAction(19, Actions.retractLift, "retract lift"),
        };

        Auton auton = new Auton(this, path, actions);

        auton.pidX = new PID(1 / 20.0, 0, 0);
        auton.pidY = new PID(1 / 20.0, 0, 0);
        auton.pidZ = new PID(1 / 20.0, 0, 0);

        auton.runOpMode();
    }

}
