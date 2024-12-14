package org.firstinspires.ftc.teamcode.test

import com.qualcomm.robotcore.eventloop.opmode.LinearOpMode
import com.qualcomm.robotcore.eventloop.opmode.TeleOp
import org.firstinspires.ftc.teamcode.Robot

@TeleOp(name = "[FTC24:test] Mecanum")
class MecanumTest : LinearOpMode() {
    lateinit var robot: Robot

    override fun runOpMode() {
        this.robot = Robot(this.hardwareMap)

        waitForStart()

        while (opModeIsActive()) {
            val forwardPower = -gamepad1.left_stick_y + 0.0
            val strafePower = gamepad1.left_stick_x + 0.0
            val turnPower = gamepad1.right_stick_x + 0.0

            this.robot.driveTrain.drive(
                forwardPower,
                turnPower,
                strafePower
            )
        }
    }

}