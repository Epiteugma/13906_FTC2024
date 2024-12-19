package org.firstinspires.ftc.teamcode.test

import com.qualcomm.robotcore.eventloop.opmode.LinearOpMode
import com.qualcomm.robotcore.eventloop.opmode.TeleOp

@TeleOp(name = "Native OpMode Test")
class Native : LinearOpMode() {

    companion object {
        init {
            System.loadLibrary("team_code")
        }
    }

    external override fun runOpMode()
}