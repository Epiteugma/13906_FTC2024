#pragma once
#include "jni.h"
#include "string"

class C_Telemetry {
    JNIEnv *p_jni;
    jobject self;

    jmethodID m_addLine;
    jmethodID m_addLineEmpty;
    jmethodID m_speak;
    jmethodID m_update;
public:
    C_Telemetry(JNIEnv *p_jni, jobject self);
    ~C_Telemetry();

    void addLine(const std::string& line);
    void addLine();
    void speak(const std::string& text);
    bool update();
};