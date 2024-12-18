#pragma once

#include <jni.h>

class C_OpMode {
    JNIEnv *p_jni;
    jobject self;

    jmethodID m_waitForStart;
    jmethodID m_opModeIsActive;
public:
    virtual void runOpMode();
    void waitForStart();
    bool opModeIsActive();

    C_OpMode(JNIEnv *p_jni, jobject self);
};