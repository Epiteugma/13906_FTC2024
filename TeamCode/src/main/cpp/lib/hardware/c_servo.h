#pragma once
#include "jni.h"

class C_Servo {
    JNIEnv *p_jni;
    jobject self;

    jmethodID m_setPosition;
public:
    C_Servo(JNIEnv *p_jni, jobject self);
    ~C_Servo();

    void setPosition(double position);
};