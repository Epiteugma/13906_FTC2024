#include "c_servo.h"

C_Servo::C_Servo(JNIEnv *p_jni, jobject self) {
    this->p_jni = p_jni;
    this->self = self;

    jclass clazz = p_jni->GetObjectClass(self);

    this->c_direction = p_jni->FindClass("com/qualcomm/robotcore/hardware/Servo$Direction");

    this->m_setPosition = p_jni->GetMethodID(clazz, "setPosition", "(D)V");
    this->m_setDirection = p_jni->GetMethodID(clazz, "setDirection", "(Lcom/qualcomm/robotcore/hardware/Servo$Direction;)V");
}

C_Servo::~C_Servo() {
    this->p_jni->DeleteLocalRef(this->self);
}

void C_Servo::setPosition(double position) {
    this->p_jni->CallVoidMethod(this->self, this->m_setPosition, position);
}

void C_Servo::setDirection(C_Direction direction) {
    std::string fieldName;

    switch (direction) {
        case FORWARD:
            fieldName = "FORWARD";
            break;
        case REVERSE:
            fieldName = "REVERSE";
            break;
    }

    jfieldID f_direction = this->p_jni->GetStaticFieldID(this->c_direction, fieldName.c_str(), "Lcom/qualcomm/robotcore/hardware/Servo$Direction;");
    jobject j_direction = this->p_jni->GetStaticObjectField(this->c_direction, f_direction);

    this->p_jni->CallVoidMethod(this->self, this->m_setDirection, j_direction);
    this->p_jni->DeleteLocalRef(j_direction);
}