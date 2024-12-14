package com.epiteugma.quartz.math

import kotlin.math.cos
import kotlin.math.sin

class Vec(
    var x: Double = 0.0,
    var y: Double = 0.0,
    var z: Double = 0.0
) {
    private fun rotationMatrix(theta: Double): Array<Array<Double>> {
        return arrayOf(
            arrayOf(cos(theta), -sin(theta)),
            arrayOf(sin(theta), cos(theta))
        )
    }

    fun add(x: Double = 0.0, y: Double = 0.0, z: Double = 0.0) {
        this.x += x
        this.y += y
        this.z += z
    }

    fun add(vec: Vec) {
        this.x += vec.x
        this.y += vec.y
        this.z += vec.z
    }

    fun rotate(theta: Double, axis: Axis) {
        val mat = this.rotationMatrix(theta)

        when (axis) {
            Axis.X -> {
                val y = this.y
                val z = this.z

                this.y = mat[0][0] * y + mat[0][1] * z
                this.z = mat[1][0] * y + mat[1][1] * z
            }
            Axis.Y -> {
                val x = this.x
                val z = this.z

                this.x = mat[0][0] * x + mat[0][1] * z
                this.z = mat[1][0] * x + mat[1][1] * z
            }
            Axis.Z -> {
                val x = this.x
                val y = this.y

                this.x = mat[0][0] * x + mat[0][1] * y
                this.y = mat[1][0] * x + mat[1][1] * y
            }
        }
    }
}