#pragma once
#include "jni.h"
#include "string"

class C_DcMotor {
    JNIEnv *p_jni;
    jobject self;

    jclass c_direction;
    jclass c_run_mode;
    jclass c_zero_power_behavior;

    jmethodID m_setPower;
    jmethodID m_setDirection;
    jmethodID m_setMode;
    jmethodID m_setZeroPowerBehavior;
    jmethodID m_setTargetPosition;
    jmethodID m_getCurrentPosition;
public:
    C_DcMotor(JNIEnv *p_jni, jobject self);
    ~C_DcMotor();

    enum C_Direction {
        FORWARD,
        REVERSE
    };

    enum C_RunMode {
        RUN_WITHOUT_ENCODER,
        RUN_USING_ENCODER,
        RUN_TO_POSITION,
        STOP_AND_RESET_ENCODER
    };

    enum C_ZeroPowerBehavior {
        UNKNOWN, // exists in SDK, but unused - made for teams to store state
        BRAKE,
        FLOAT
    };

    void setPower(double power);
    void setDirection(C_Direction direction);
    void setMode(C_RunMode runMode);
    void setZeroPowerBehavior(C_ZeroPowerBehavior zeroPowerBehavior);
    void setTargetPosition(int targetPosition);
    int getCurrentPosition();
};