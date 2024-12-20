#pragma once
#include "jni.h"

class C_Gamepad {
    JNIEnv *p_jni;
    jobject self;

    jfieldID f_left_stick_x;
    jfieldID f_left_stick_y;
    jfieldID f_right_stick_x;
    jfieldID f_right_stick_y;
    jfieldID f_left_stick_button;
    jfieldID f_right_stick_button;

    jfieldID f_dpad_down;
    jfieldID f_dpad_up;
    jfieldID f_dpad_left;
    jfieldID f_dpad_right;

    jfieldID f_a;
    jfieldID f_b;
    jfieldID f_x;
    jfieldID f_y;

    jfieldID f_left_bumper;
    jfieldID f_left_trigger;
    jfieldID f_right_bumper;
    jfieldID f_right_trigger;
public:
    C_Gamepad(JNIEnv *p_jni, jobject self);
    ~C_Gamepad();

    float left_stick_x();
    float left_stick_y();
    float right_stick_x();
    float right_stick_y();
    bool left_stick_button();
    bool right_stick_button();

    bool dpad_down();
    bool dpad_up();
    bool dpad_left();
    bool dpad_right();

    bool a();
    bool b();
    bool x();
    bool y();

    // PS controller support
    bool cross();
    bool circle();
    bool square();
    bool triangle();

    bool left_bumper();
    float left_trigger();
    bool right_bumper();
    float right_trigger();
};