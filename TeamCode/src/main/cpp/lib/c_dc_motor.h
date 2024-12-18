#pragma once
#include "jni.h"
#include "string"

class C_DcMotor {
    JNIEnv *p_jni;
    jobject self;

    jclass c_direction;
    jclass c_run_mode;

    jmethodID m_setPower;
    jmethodID m_setDirection;
    jmethodID m_setMode;
public:
    C_DcMotor(JNIEnv *p_jni, jobject self);

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

    void setPower(double power);
    void setDirection(C_Direction direction);
    void setMode(C_RunMode runMode);
};