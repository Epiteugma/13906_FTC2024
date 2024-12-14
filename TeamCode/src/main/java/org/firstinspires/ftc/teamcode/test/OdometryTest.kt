package org.firstinspires.ftc.teamcode.test

import com.epiteugma.quartz.Odometry
import com.epiteugma.quartz.math.TickDistance
import com.qualcomm.robotcore.eventloop.opmode.Autonomous
import com.qualcomm.robotcore.eventloop.opmode.LinearOpMode
import org.firstinspires.ftc.teamcode.Robot
import kotlin.math.PI

@Autonomous(name = "[FTC24:test] Odometry")
class OdometryTest : LinearOpMode() {
    private lateinit var robot: Robot
    private lateinit var odometry: Odometry
    private val converter = TickDistance(28, 20.0, 0.0)

    override fun runOpMode() {
        this.robot = Robot(this.hardwareMap)
        this.odometry = Odometry(
            Odometry.Parameters(
                converter.toTicks(0.0)
            ),
            this.robot.driveTrain.frontLeft,
            this.robot.driveTrain.frontRight
        )

        waitForStart()

        while (opModeIsActive()) {
            this.odometry.update()

            this.telemetry.addLine("x = %.2f".format(converter.toDistance(this.odometry.pose.x.toInt())))
            this.telemetry.addLine("y = %.2f".format(converter.toDistance(this.odometry.pose.y.toInt())))
            this.telemetry.addLine("theta = %.2f".format(this.odometry.theta / PI * 180.0))
            this.telemetry.update()
        }
    }

}