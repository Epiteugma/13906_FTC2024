#pragma once
#include "jni.h"

class C_Gamepad {
    JNIEnv *p_jni;
    jobject self;

    jfieldID f_left_stick_x;
    jfieldID f_left_stick_y;

    jfieldID f_right_stick_x;
    jfieldID f_right_stick_y;
public:
    C_Gamepad(JNIEnv *p_jni, jobject self);

    float left_stick_x();
    float left_stick_y();

    float right_stick_x();
    float right_stick_y();
};