#pragma once
#include "jni.h"
#include "string"

class C_Telemetry {
    JNIEnv *p_jni;
    jobject self;

    jmethodID m_addLine;
    jmethodID m_update;
public:
    C_Telemetry(JNIEnv *p_jni, jobject self);
    ~C_Telemetry();

    void addLine(const std::string& line);
    bool update();
};