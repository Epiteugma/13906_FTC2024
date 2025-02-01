#include "c_touchsensor.h"

C_TouchSensor::C_TouchSensor(JNIEnv *p_jni, jobject self) {
    this->p_jni = p_jni;
    this->self = self;

    jclass clazz = this->p_jni->GetObjectClass(self);

    this->m_getValue = this->p_jni->GetMethodID(clazz, "getValue", "()D");
    this->m_isPressed = this->p_jni->GetMethodID(clazz, "isPressed", "()B");
}

double C_TouchSensor::getValue() {
    return this->p_jni->CallDoubleMethod(this->self, this->m_getValue);
}

bool C_TouchSensor::isPressed() {
    return this->p_jni->CallBooleanMethod(this->self, this->m_isPressed);
}