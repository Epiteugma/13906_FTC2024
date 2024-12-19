#pragma once

#include <jni.h>
#include "hardware/c_hardware_map.h"
#include "c_gamepad.h"
#include "c_telemetry.h"

class C_OpMode {
    JNIEnv *p_jni;
    jobject self;

    jmethodID m_waitForStart;
    jmethodID m_opModeIsActive;
public:
    C_HardwareMap *hardwareMap;
    C_Telemetry *telemetry;
    C_Gamepad *gamepad1;
    C_Gamepad *gamepad2;

    virtual void runOpMode();
    void waitForStart();
    bool opModeIsActive();

    C_OpMode(JNIEnv *p_jni, jobject self);
};