package org.firstinspires.ftc.teamcode.opmodes;

import com.qualcomm.robotcore.eventloop.opmode.Autonomous;
import com.qualcomm.robotcore.eventloop.opmode.LinearOpMode;

import org.firstinspires.ftc.teamcode.Constants;
import org.firstinspires.ftc.teamcode.auton.Actions;
import org.firstinspires.ftc.teamcode.auton.Auton;
import org.firstinspires.ftc.teamcode.auton.AutonAction;
import org.firstinspires.ftc.teamcode.utils.PID;
import org.firstinspires.ftc.teamcode.utils.maths.Vec3;

@Autonomous(name = "[FTC24] Place Blue")
public class AutonPlaceBlue extends LinearOpMode {

    @Override
    public void runOpMode() {
        if (Constants.PRACTICE_BOT) return; // ONLY RUN AUTON ON REAL BOT

        Vec3[] path = new Vec3[]{
                new Vec3(-30, -60, 0),
                new Vec3(-30, -60, -40),
                new Vec3(-7, -74, -40), // score block 2
                new Vec3(-30, -50, -40),
                new Vec3(-30, -50, -185),
                new Vec3(-30, -20, -185),
                new Vec3(-91, -15, -185),
                new Vec3(-91, -25, -185),
                new Vec3(-40, -60, -185),
                new Vec3(-40, -60, -40),
                new Vec3(-10, -75, -40), // score block 2
                new Vec3(-40, -60, -40),
                new Vec3(-40, -60, -180),
                new Vec3(-40, -15, -180),
                new Vec3(-90, -15, -180),
                new Vec3(-90, -45, -180),
                new Vec3(-40, -45, -180),
                new Vec3(-40, -45, -25),
                new Vec3(-10, -78, -25),
                new Vec3(-40, -60, -25),
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
