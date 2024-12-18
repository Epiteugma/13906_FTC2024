#include "c_dc_motor.h"

C_DcMotor::C_DcMotor(JNIEnv *p_jni, jobject self) {
    this->p_jni = p_jni;
    this->self = self;

    jclass clazz = p_jni->GetObjectClass(self);

    this->c_direction = p_jni->FindClass("com/qualcomm/robotcore/hardware/DcMotorSimple$Direction");
    this->c_run_mode = p_jni->FindClass("com/qualcomm/robotcore/hardware/DcMotor$RunMode");

    this->m_setPower = p_jni->GetMethodID(clazz, "setPower", "(D)V");
    this->m_setDirection = p_jni->GetMethodID(clazz, "setDirection", "(Lcom/qualcomm/robotcore/hardware/DcMotorSimple$Direction;)V");
    this->m_setMode = p_jni->GetMethodID(clazz, "setMode", "(Lcom/qualcomm/robotcore/hardware/DcMotor$RunMode;)V");
}

void C_DcMotor::setPower(double power) {
    this->p_jni->CallVoidMethod(this->self, this->m_setPower, (jdouble) power);
}

void C_DcMotor::setDirection(C_DcMotor::C_Direction direction) {
    std::string fieldName;

    switch (direction) {
        case FORWARD:
            fieldName = "FORWARD";
            break;
        case REVERSE:
            fieldName = "REVERSE";
            break;
    }

    jfieldID j_dir = this->p_jni->GetStaticFieldID(this->c_direction, fieldName.c_str(), "Lcom/qualcomm/robotcore/hardware/DcMotorSimple$Direction;");
    this->p_jni->CallVoidMethod(this->self, this->m_setDirection, j_dir);
}

void C_DcMotor::setMode(C_DcMotor::C_RunMode runMode) {
    std::string fieldName;

    switch (runMode) {
        case RUN_USING_ENCODER:
            fieldName = "RUN_USING_ENCODER";
            break;
        case RUN_WITHOUT_ENCODER:
            fieldName = "RUN_WITHOUT_ENCODER";
            break;
        case RUN_TO_POSITION:
            fieldName = "RUN_TO_POSITION";
            break;
        case STOP_AND_RESET_ENCODER:
            fieldName = "STOP_AND_RESET_ENCODER";
            break;
    }

    jfieldID j_mode = this->p_jni->GetStaticFieldID(this->c_direction, fieldName.c_str(), "Lcom/qualcomm/robotcore/hardware/DcMotor$RunMode;");
    this->p_jni->CallVoidMethod(this->self, this->m_setMode, j_mode);
}