#include "c_telemetry.h"

C_Telemetry::C_Telemetry(JNIEnv* p_jni, jobject self) {
    this->p_jni = p_jni;
    this->self = self;

    jclass clazz = p_jni->GetObjectClass(self);

    this->m_addLine = p_jni->GetMethodID(clazz, "addLine", "(Ljava/lang/String;)Lorg/firstinspires/ftc/robotcore/external/Telemetry$Line;");
    this->m_addLineEmpty = p_jni->GetMethodID(clazz, "addLine", "()Lorg/firstinspires/ftc/robotcore/external/Telemetry$Line;");
    this->m_speak = p_jni->GetMethodID(clazz, "speak", "(Ljava/lang/String;)V");
    this->m_update = p_jni->GetMethodID(clazz, "update", "()Z");
}

C_Telemetry::~C_Telemetry() {
    this->p_jni->DeleteLocalRef(this->self);
}

void C_Telemetry::addLine(const std::string& line) {
    jstring j_line = this->p_jni->NewStringUTF(line.c_str());

    this->p_jni->DeleteLocalRef(this->p_jni->CallObjectMethod(this->self, this->m_addLine, j_line));
    this->p_jni->DeleteLocalRef(j_line);
}

void C_Telemetry::addLine() {
    this->p_jni->DeleteLocalRef(this->p_jni->CallObjectMethod(this->self, this->m_addLineEmpty));
}

void C_Telemetry::speak(const std::string& text) {
    jstring j_text = this->p_jni->NewStringUTF(text.c_str());

    this->p_jni->CallVoidMethod(this->self, this->m_speak, j_text);
    this->p_jni->DeleteLocalRef(j_text);
}

bool C_Telemetry::update() {
    return (bool) this->p_jni->CallBooleanMethod(this->self, this->m_update);
}