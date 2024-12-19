#include "c_hardware_map.h"

C_HardwareMap::C_HardwareMap(JNIEnv *p_jni, jobject self) {
    this->p_jni = p_jni;
    this->self = self;

    jclass clazz = p_jni->GetObjectClass(self);

    this->m_get = p_jni->GetMethodID(clazz, "get", "(Ljava/lang/Object;Ljava/lang/String;)Ljava/lang/Object;");
}

C_DcMotor *C_HardwareMap::getDcMotor(const std::string& name) {
    return new C_DcMotor(this->p_jni, this->p_jni->CallObjectMethod(this->self, this->m_get, this->p_jni->FindClass("com/qualcomm/robotcore/hardware/DcMotor"), (jstring) name.c_str()));
}

C_Servo *C_HardwareMap::getServo(const std::string& name) {
    return new C_Servo(this->p_jni, this->p_jni->CallObjectMethod(this->self, this->m_get, this->p_jni->FindClass("com/qualcomm/robotcore/hardware/Servo"), (jstring) name.c_str()));
}
