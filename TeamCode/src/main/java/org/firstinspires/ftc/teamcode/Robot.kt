package org.firstinspires.ftc.teamcode

import com.epiteugma.quartz.DriveTrain
import com.qualcomm.robotcore.hardware.DcMotor
import com.qualcomm.robotcore.hardware.HardwareMap

class Robot(hardwareMap: HardwareMap) {
    val driveTrain = DriveTrain(
        hardwareMap.get(DcMotor::class.java, "frontLeft"),
        hardwareMap.get(DcMotor::class.java, "frontRight"),
        hardwareMap.get(DcMotor::class.java, "backLeft"),
        hardwareMap.get(DcMotor::class.java, "backRight")
    )
}