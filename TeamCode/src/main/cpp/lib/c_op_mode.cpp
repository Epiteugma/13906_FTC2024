#include "c_op_mode.h"

C_OpMode::C_OpMode(JNIEnv *p_jni, jobject self) {
    this->p_jni = p_jni;
    this->self = self;

    jclass clazz = p_jni->GetObjectClass(self);

    this->m_opModeIsActive = p_jni->GetMethodID(clazz, "opModeIsActive", "()Z");
    this->m_waitForStart = p_jni->GetMethodID(clazz, "waitForStart", "()V");

    this->hardwareMap = new C_HardwareMap(p_jni, p_jni->GetObjectField(self, p_jni->GetFieldID(clazz, "hardwareMap", "Lcom/qualcomm/robotcore/hardware/HardwareMap;")));
    this->gamepad1 = new C_Gamepad(p_jni, p_jni->GetObjectField(self, p_jni->GetFieldID(clazz, "gamepad1", "Lcom/qualcomm/robotcore/hardware/Gamepad;")));
    this->gamepad2 = new C_Gamepad(p_jni, p_jni->GetObjectField(self, p_jni->GetFieldID(clazz, "gamepad2", "Lcom/qualcomm/robotcore/hardware/Gamepad;")));
}

bool C_OpMode::opModeIsActive() {
    return (bool) this->p_jni->CallBooleanMethod(this->self, this->m_opModeIsActive);
}

void C_OpMode::waitForStart() {
    this->p_jni->CallVoidMethod(this->self, this->m_waitForStart);
}

void C_OpMode::runOpMode() {}
