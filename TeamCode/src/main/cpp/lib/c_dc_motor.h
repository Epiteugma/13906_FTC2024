#pragma once
#include "jni.h"

class C_DcMotor {
    JNIEnv *p_jni;
    jobject self;

    jmethodID m_setPower;
public:
    C_DcMotor(JNIEnv *p_jni, jobject self);

    void setPower(double power);
};