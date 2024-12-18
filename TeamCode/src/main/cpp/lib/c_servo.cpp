#include "c_servo.h"

C_Servo::C_Servo(JNIEnv *p_jni, jobject self) {
    this->p_jni = p_jni;
    this->self = self;
}