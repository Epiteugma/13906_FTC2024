#include "odometry_test.h"
#include "../../utils/utils.h"
#include "../../utils/maths.h"
#include "../../utils/odometry/odometry.h"

extern "C"
JNIEXPORT void JNICALL Java_org_firstinspires_ftc_teamcode_opmodes_test_Odometry_runOpMode(JNIEnv *p_jni, jobject self) {
    (new OdometryTest(p_jni, self))->runOpMode();
}

void OdometryTest::runOpMode() {
    auto left = this->hardwareMap->getDcMotor("par_l");
    auto right = this->hardwareMap->getDcMotor("par_r");
    auto perp = this->hardwareMap->getDcMotor("perp");
    double track_width = math::distanceToTicks(45.0, 4.5, 8192);
    double forward_offset = math::distanceToTicks(-23.0, 4.5, 8192);

    right->setDirection(C_DcMotor::C_Direction::REVERSE);
    perp->setDirection(C_DcMotor::C_Direction::REVERSE);

    this->waitForStart();

    int last_left = left->getCurrentPosition();
    int last_right = right->getCurrentPosition();
    int last_perp = perp->getCurrentPosition();

    math::vec2 pos{};
    double theta = 0;

    while (this->opModeIsActive()) {
        int delta_left = left->getCurrentPosition() - last_left;
        int delta_right = right->getCurrentPosition() - last_right;
        int delta_perp = perp->getCurrentPosition() - last_perp;

        last_left += delta_left;
        last_right += delta_right;
        last_perp += delta_perp;

        double phi = (delta_right - delta_left) / track_width;
        math::vec2 deltas{
            delta_perp + (forward_offset * phi),
            (delta_right + delta_left) / 2.0
        };

        this->telemetry->addLine(utils::sprintf("(deltas, rel) x = %.2f; y = %.2f", deltas.x, deltas.y));
        deltas.rotate(theta);

        pos.x += deltas.x;
        pos.y += deltas.y;
        theta += phi;

        this->telemetry->addLine(utils::sprintf("(deltas, global) x = %.2f; y = %.2f", deltas.x, deltas.y));

        this->telemetry->addLine(utils::sprintf(
                "(position) x = %.2f; y = %.2f; θ = %.2f",
                math::ticksToDistance(pos.x, 4.5, 8192),
                math::ticksToDistance(pos.y, 4.5, 8192),
                theta / M_PI * 180.0
        ));

        this->telemetry->update();
    }
}