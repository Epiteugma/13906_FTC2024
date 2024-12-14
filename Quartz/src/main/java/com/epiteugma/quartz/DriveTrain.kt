package com.epiteugma.quartz

import com.qualcomm.robotcore.hardware.DcMotor

class DriveTrain(
    val frontLeft: DcMotor,
    val frontRight: DcMotor,
    val backLeft: DcMotor?,
    val backRight: DcMotor?
) {
    fun drive(
        forwardPower: Double,
        turnPower: Double,
        strafePower: Double? = 0.0
    ) {
        this.frontLeft.power = forwardPower + turnPower + (strafePower ?: 0.0)
        this.frontRight.power = forwardPower - turnPower - (strafePower ?: 0.0)

        if (this.backLeft != null) this.backLeft.power = forwardPower + turnPower - (strafePower ?: 0.0)
        if (this.backRight != null) this.backRight.power = forwardPower - turnPower + (strafePower ?: 0.0)
    }
}