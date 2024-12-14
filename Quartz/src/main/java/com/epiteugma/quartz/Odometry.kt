package com.epiteugma.quartz

import com.epiteugma.quartz.math.Axis
import com.epiteugma.quartz.math.Vec
import com.qualcomm.robotcore.hardware.DcMotor

class Odometry(
    val params: Parameters,
    val left: DcMotor,
    val right: DcMotor,
    val parallel: DcMotor?
) {
    class Parameters(
        val trackWidth: Int,
        val parallelOffset: Int?
    )

    val pose = Vec()
    var theta = 0.0

    private var lastLeft = 0
    private var lastRight = 0
    private var lastParallel = 0

    fun update() {
        val deltaLeft = this.left.currentPosition - lastLeft
        val deltaRight = this.right.currentPosition - lastRight
        val deltaParallel = (this.parallel?.currentPosition ?: 0) - lastParallel

        this.reset()

        val phi = (deltaRight - deltaLeft) / this.params.trackWidth
        val deltas = Vec(
            deltaParallel.toDouble() - (this.params.parallelOffset ?: 0) * phi,
            (deltaRight + deltaLeft) / 2.0
        )

        deltas.rotate(this.theta, Axis.Z)

        this.theta += phi
        this.pose.add(deltas)
    }

    fun reset() {
        this.lastLeft = this.left.currentPosition
        this.lastRight = this.right.currentPosition
        this.lastParallel = this.parallel?.currentPosition ?: 0
    }
}