#include "servo_tuner.h"
#include "chrono"

extern "C"
JNIEXPORT void JNICALL Java_org_firstinspires_ftc_teamcode_opmodes_ServoTuner_runOpMode(JNIEnv *p_jni, jobject self) {
    (new ServoTuner(p_jni, self))->runOpMode();
}

void ServoTuner::runOpMode() {
    this->waitForStart();

    std::string servo_name = "release";
    double position = 0.0;

    auto last = std::chrono::high_resolution_clock::now();
    auto servo = this->hardwareMap->getServo(servo_name);

    while (this->opModeIsActive()) {
        auto now = std::chrono::high_resolution_clock::now();
        long delta = std::chrono::duration_cast<std::chrono::microseconds>(now - last).count();
        last = now;

        double moveDelta = (double) delta / 5000000.0; // 5 sec
        position += -this->gamepad1->left_stick_y() * moveDelta;

        if (position < 0.0) position = 0.0;
        if (position > 1.0) position = 1.0;

        servo->setPosition(position);

        char name_telem[100];
        sprintf(name_telem, "servo name = %s", servo_name.c_str());
        this->telemetry->addLine(name_telem);

        char position_telem[100];
        sprintf(position_telem, "servo position = %.2f", position);
        this->telemetry->addLine(position_telem);

        this->telemetry->update();
    }
}