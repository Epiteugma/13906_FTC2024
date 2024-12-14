package com.epiteugma.quartz

import com.epiteugma.quartz.math.Axis
import com.epiteugma.quartz.math.Vec

class DriveOdometry(
    val driveTrain: DriveTrain,
    val trackWidth: Int,
    val mode: Mode = Mode.FOUR_WHEEL
) {
    val pose = Vec()
    var theta = 0.0

    enum class Mode {
        TWO_WHEEL,
        FOUR_WHEEL
    }

    private var lastFrontLeft = 0
    private var lastFrontRight = 0
    private var lastBackLeft = 0
    private var lastBackRight = 0

    fun update() {
        val deltaFrontLeft = this.driveTrain.frontLeft.currentPosition - this.lastFrontLeft
        val deltaFrontRight = this.driveTrain.frontRight.currentPosition - this.lastFrontRight
        val deltaBackLeft = (this.driveTrain.backLeft?.currentPosition ?: 0) - this.lastBackLeft
        val deltaBackRight = (this.driveTrain.backRight?.currentPosition ?: 0) - this.lastBackRight

        this.reset()

        var averageDelta = (deltaFrontRight + deltaFrontLeft) / 2.0
        var phi = (deltaFrontRight - deltaFrontLeft) / this.trackWidth.toDouble()

        if (this.mode == Mode.FOUR_WHEEL &&
            this.driveTrain.backLeft != null &&
            this.driveTrain.backRight != null
        ) {
            val backAverage = (deltaBackRight + deltaBackLeft) / 2.0
            averageDelta = (averageDelta + backAverage) / 2.0

            val backPhi = (deltaBackRight - deltaBackLeft) / this.trackWidth.toDouble()
            phi = (phi + backPhi) / 2.0
        }

        val delta = Vec(
            0.0,
            averageDelta
        )

        delta.rotate(this.theta, Axis.Z)

        this.theta += phi
        this.pose.add(delta)
    }

    fun reset() {
        this.lastFrontLeft = this.driveTrain.frontLeft.currentPosition
        this.lastFrontRight = this.driveTrain.frontRight.currentPosition
        this.lastBackLeft = this.driveTrain.backLeft?.currentPosition ?: 0
        this.lastBackRight = this.driveTrain.backRight?.currentPosition ?: 0
    }
}