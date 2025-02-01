#pragma once
#include "jni.h"

class C_TouchSensor {
    JNIEnv *p_jni;
    jobject self;

    jmethodID m_getValue;
    jmethodID m_isPressed;
public:
    C_TouchSensor(JNIEnv *p_jni, jobject self);

    double getValue();
    bool isPressed();
};
