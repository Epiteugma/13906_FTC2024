#include "c_servo.h"

C_Servo::C_Servo(JNIEnv *p_jni, jobject self) {
    this->p_jni = p_jni;
    this->self = self;

    jclass clazz = p_jni->GetObjectClass(self);

    this->m_setPosition = p_jni->GetMethodID(clazz, "setPosition", "(D)V");
}

void C_Servo::setPosition(double position) {
    this->p_jni->CallVoidMethod(this->self, this->m_setPosition, (jdouble) position);
}