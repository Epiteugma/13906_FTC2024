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
        45.0 * o_ticks_per_cm,
        -o.track_width / 2.0,
    };

    o.right->setDirection(C_DcMotor::REVERSE);
    o.perp->setDirection(C_DcMotor::REVERSE);

    this->waitForStart();
    o.init();

    std::map<double, std::vector<double>> mappuchino{};
    auto start = std::chrono::system_clock::now();

    while (this->opModeIsActive()) {
        std::chrono::duration<double> time_since_start = (std::chrono::system_clock::now() - start);
        auto millis = (long long) (time_since_start.count() * 1000);

        if (time_since_start.count() > 30.0) break;

        double out = std::sin((int) (millis % 5000) / 5000.0 * 2 * M_PI) * 0.3;

        d.drive(out, 0.0);
        o.update();

        this->telemetry->addLine(utils::sprintf("== BENCHMARKING... %.2fs ==", 30.0 - time_since_start.count()));

        if (mappuchino.find(out) == mappuchino.end()) {
            mappuchino[out] = {};
        }

        mappuchino[out].push_back(std::hypot(o.velocity.x / o_ticks_per_cm, o.velocity.y / o_ticks_per_cm));

        this->telemetry->addLine(utils::sprintf("x = %.2f", o.pos.x / o_ticks_per_cm));
        this->telemetry->addLine(utils::sprintf("y = %.2f", o.pos.y / o_ticks_per_cm));
        this->telemetry->addLine(utils::sprintf("theta = %.2f", o.theta / M_PI * 180.0));
        this->telemetry->update();
    }

    d.drive(0.0, 0.0);

    double v_max = 0.0;
    double p_at_v_max = -1.0;

    double p_at_v0_sum = 0.0;
    int p_at_v0_count = 0;

    long p_count = 0;
    long v_count = 0;

    for (auto &pow : mappuchino) {
        p_count++;

        for (auto vel : pow.second) {
            v_count++;

            if (vel > v_max) {
                v_max = vel;
                p_at_v_max = std::abs(pow.first);
            }

            if (std::abs(vel) < 1.0) {
                p_at_v0_sum += pow.first;
                p_at_v0_count++;
            }
        }
    }

    double avg_p_at_v0 = p_at_v0_sum / (double) p_at_v0_count;

    this->telemetry->speak("benchmark complete");

    while (this->opModeIsActive()) {
        this->telemetry->addLine(utils::sprintf("v_max = %.2f", v_max));
        this->telemetry->addLine(utils::sprintf("p_at_v_max = %.2f", p_at_v_max));
        this->telemetry->addLine(utils::sprintf("avg_p_at_v0 = %.2f", avg_p_at_v0));

        this->telemetry->addLine();
        this->telemetry->addLine(utils::sprintf("p_count = %ld", p_count));
        this->telemetry->addLine(utils::sprintf("v_count = %ld", v_count));

        this->telemetry->addLine();
        this->telemetry->addLine("== BENCHMARK COMPLETE ==");
        this->telemetry->update();
    }
}