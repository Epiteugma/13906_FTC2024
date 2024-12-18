#include "c_gamepad.h"

C_Gamepad::C_Gamepad(JNIEnv *p_jni, jobject self) {
    this->p_jni = p_jni;
    this->self = self;

    jclass clazz = p_jni->GetObjectClass(self);

    this->f_left_stick_x = p_jni->GetFieldID(clazz, "left_stick_x", "F");
    this->f_left_stick_y = p_jni->GetFieldID(clazz, "left_stick_y", "F");

    this->f_right_stick_x = p_jni->GetFieldID(clazz, "right_stick_x", "F");
    this->f_right_stick_y = p_jni->GetFieldID(clazz, "right_stick_y", "F");
}

float C_Gamepad::left_stick_x() {
    return this->p_jni->GetFloatField(this->self, this->f_left_stick_x);
}

float C_Gamepad::left_stick_y() {
    return this->p_jni->GetFloatField(this->self, this->f_left_stick_y);
}

float C_Gamepad::right_stick_x() {
    return this->p_jni->GetFloatField(this->self, this->f_right_stick_x);
}

float C_Gamepad::right_stick_y() {
    return this->p_jni->GetFloatField(this->self, this->f_right_stick_y);
}