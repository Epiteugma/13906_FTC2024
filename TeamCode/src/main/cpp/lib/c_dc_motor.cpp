#include "c_dc_motor.h"

C_DcMotor::C_DcMotor(JNIEnv *p_jni, jobject self) {
    this->p_jni = p_jni;
    this->self = self;

    jclass clazz = p_jni->GetObjectClass(self);

    this->m_setPower = p_jni->GetMethodID(clazz, "setPower", "(D)V");
}

void C_DcMotor::setPower(double power) {
    this->p_jni->CallVoidMethod(this->self, this->m_setPower, (jdouble) power);
}