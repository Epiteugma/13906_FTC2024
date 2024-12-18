#pragma once
#include "jni.h"

class C_Servo {
    JNIEnv *p_jni;
    jobject self;
public:
    C_Servo(JNIEnv *p_jni, jobject self);
};