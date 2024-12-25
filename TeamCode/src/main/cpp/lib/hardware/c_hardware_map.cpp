#include "c_hardware_map.h"

C_HardwareMap::C_HardwareMap(JNIEnv *p_jni, jobject self) {
    this->p_jni = p_jni;
    this->self = self;

    jclass clazz = p_jni->GetObjectClass(self);

    this->m_get = p_jni->GetMethodID(clazz, "get", "(Ljava/lang/Class;Ljava/lang/String;)Ljava/lang/Object;");
}

C_HardwareMap::~C_HardwareMap() {
    this->p_jni->DeleteLocalRef(this->self);
};

C_DcMotor *C_HardwareMap::getDcMotor(const std::string& name) {
    jstring j_name = this->p_jni->NewStringUTF(name.c_str());

    auto *motor = new C_DcMotor(this->p_jni, this->p_jni->CallObjectMethod(this->self, this->m_get, this->p_jni->FindClass("com/qualcomm/robotcore/hardware/DcMotorEx"), j_name));
    this->p_jni->DeleteLocalRef(j_name);

    return motor;
}

C_Servo *C_HardwareMap::getServo(const std::string& name) {
    jstring j_name = this->p_jni->NewStringUTF(name.c_str());

    auto* servo = new C_Servo(this->p_jni, this->p_jni->CallObjectMethod(this->self, this->m_get, this->p_jni->FindClass("com/qualcomm/robotcore/hardware/Servo"), j_name));
    this->p_jni->DeleteLocalRef(j_name);

    return servo;
}
