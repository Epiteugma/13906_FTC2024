#include "regressor_test.h"

extern "C"
JNIEXPORT void JNICALL Java_org_firstinspires_ftc_teamcode_opmodes_RegressorTest_runOpMode(JNIEnv *p_jni, jobject self) {
    (new RegressorTest(p_jni, self))->runOpMode();
}

void RegressorTest::runOpMode() {
    this->robot = new Robot(this);

    this->waitForStart();

    while (this->opModeIsActive()) {
        this->robot->odometry->update();
    }
}