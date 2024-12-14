package com.epiteugma.quartz.math

import kotlin.math.PI

class TickDistance(
    val motorTPR: Int,
    val gearbox: Double,
    val wheelRadius: Double
) {
    fun toTicks(distance: Double): Int {
        return (distance / (2 * PI * wheelRadius) * (gearbox * motorTPR)).toInt()
    }

    fun toDistance(ticks: Int): Double {
        return ticks.toDouble() / (gearbox * motorTPR) * (2 * PI * wheelRadius)
    }
}