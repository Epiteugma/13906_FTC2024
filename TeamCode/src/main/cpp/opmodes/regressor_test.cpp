#include "regressor_test.h"

extern "C"
JNIEXPORT void JNICALL Java_org_firstinspires_ftc_teamcode_opmodes_RegressorTest_runOpMode(JNIEnv *p_jni, jobject self) {
    (new RegressorTest(p_jni, self))->runOpMode();
}

void RegressorTest::runOpMode() {
    auto back_left = this->hardwareMap->getDcMotor("back_left");
    auto back_right = this->hardwareMap->getDcMotor("back_right");
    auto front_left = this->hardwareMap->getDcMotor("front_left");
    auto front_right = this->hardwareMap->getDcMotor("front_right");

    Drivetrain d{
        front_left,
        front_right,
        back_left,
        back_right,
    };

    front_left->setDirection(C_DcMotor::REVERSE);
    front_right->setDirection(C_DcMotor::REVERSE);

    const double o_wheel_radius = 4.5;
    const double o_ticks_per_cm = 8192.0 / (2.0 * M_PI * o_wheel_radius);

    Odometry o{
        this->hardwareMap->getDcMotor("left_encoder"),
        this->hardwareMap->getDcMotor("right_encoder"),
        this->hardwareMap->getDcMotor("perp_encoder"),
        45.72 * o_ticks_per_cm,
        -o.track_width / 2.0,
    };

    o.right->setDirection(C_DcMotor::REVERSE);
    o.perp->setDirection(C_DcMotor::REVERSE);

    this->waitForStart();
    o.init();

    while (this->opModeIsActive()) {
        std::chrono::duration<double> time_since_epoch = std::chrono::high_resolution_clock::now().time_since_epoch();
        auto millis = (long long) (time_since_epoch.count() * 1000);

        double out = std::sin((int) (millis % 5000) / 5000.0 * 2 * M_PI);

        d.drive(out * 0.2, 0.0);
        o.update();

        this->telemetry->addLine(utils::sprintf("x = %.2f", o.pos.x / o_ticks_per_cm));
        this->telemetry->addLine(utils::sprintf("y = %.2f", o.pos.y / o_ticks_per_cm));
        this->telemetry->addLine(utils::sprintf("theta = %.2f", o.theta / M_PI * 180.0));
        this->telemetry->update();
    }
}