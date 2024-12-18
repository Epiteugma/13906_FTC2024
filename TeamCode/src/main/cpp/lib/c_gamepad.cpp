#include "c_gamepad.h"

C_Gamepad::C_Gamepad(JNIEnv *p_jni, jobject self) {
    this->p_jni = p_jni;
    this->self = self;

    jclass clazz = p_jni->GetObjectClass(self);

    this->f_left_stick_x = p_jni->GetFieldID(clazz, "left_stick_x", "F");
    this->f_left_stick_y = p_jni->GetFieldID(clazz, "left_stick_y", "F");
    this->f_right_stick_x = p_jni->GetFieldID(clazz, "right_stick_x", "F");
    this->f_right_stick_y = p_jni->GetFieldID(clazz, "right_stick_y", "F");

    this->f_dpad_down = p_jni->GetFieldID(clazz, "dpad_down", "Z");
    this->f_dpad_up = p_jni->GetFieldID(clazz, "dpad_up", "Z");
    this->f_dpad_left = p_jni->GetFieldID(clazz, "dpad_left", "Z");
    this->f_dpad_right = p_jni->GetFieldID(clazz, "dpad_right", "Z");

    this->f_a = p_jni->GetFieldID(clazz, "a", "Z");
    this->f_b = p_jni->GetFieldID(clazz, "b", "Z");
    this->f_x = p_jni->GetFieldID(clazz, "x", "Z");
    this->f_y = p_jni->GetFieldID(clazz, "y", "Z");
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

bool C_Gamepad::dpad_down() {
    return this->p_jni->GetBooleanField(this->self, this->f_dpad_down);
}

bool C_Gamepad::dpad_up() {
    return this->p_jni->GetBooleanField(this->self, this->f_dpad_up);
}

bool C_Gamepad::dpad_left() {
    return this->p_jni->GetBooleanField(this->self, this->f_dpad_left);
}

bool C_Gamepad::dpad_right() {
    return this->p_jni->GetBooleanField(this->self, this->f_dpad_right);
}

bool C_Gamepad::a() {
    return this->p_jni->GetBooleanField(this->self, this->f_a);
}

bool C_Gamepad::b() {
    return this->p_jni->GetBooleanField(this->self, this->f_b);
}

bool C_Gamepad::x() {
    return this->p_jni->GetBooleanField(this->self, this->f_x);
}

bool C_Gamepad::y() {
    return this->p_jni->GetBooleanField(this->self, this->f_y);
}