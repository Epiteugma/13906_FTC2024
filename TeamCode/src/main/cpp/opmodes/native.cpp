#include "native.h"

void Native::runOpMode() {
    this->waitForStart();

    while (this->opModeIsActive()) {
        // yay!
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_org_firstinspires_ftc_teamcode_test_Native_runOpMode(JNIEnv *p_jni, jobject self) {
    auto *opMode = new Native(p_jni, self);
    opMode->runOpMode();
}