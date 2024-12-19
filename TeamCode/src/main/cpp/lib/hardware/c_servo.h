#pragma once
#include "jni.h"
#include "string"

class C_Servo {
    JNIEnv *p_jni;
    jobject self;

    jclass c_direction;

    jmethodID m_setPosition;
    jmethodID m_setDirection;
public:
    C_Servo(JNIEnv *p_jni, jobject self);
    ~C_Servo();

    enum C_Direction {
        FORWARD,
        REVERSE
    };

    void setPosition(double position);
    void setDirection(C_Direction direction);
};