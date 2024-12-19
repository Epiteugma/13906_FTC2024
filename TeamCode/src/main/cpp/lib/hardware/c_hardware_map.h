#pragma once
#include "jni.h"
#include "string"

#include "c_dc_motor.h"
#include "c_servo.h"

class C_HardwareMap {
    JNIEnv *p_jni;
    jobject self;

    jmethodID m_get;
public:
    C_HardwareMap(JNIEnv *p_jni, jobject self);
    ~C_HardwareMap();

    C_DcMotor *getDcMotor(const std::string& name);
    C_Servo *getServo(const std::string& name);
};