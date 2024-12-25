#include "c_dc_motor.h"

C_DcMotor::C_DcMotor(JNIEnv *p_jni, jobject self) {
    this->p_jni = p_jni;
    this->self = self;

    jclass clazz = p_jni->GetObjectClass(self);

    this->c_direction = p_jni->FindClass("com/qualcomm/robotcore/hardware/DcMotorSimple$Direction");
    this->c_run_mode = p_jni->FindClass("com/qualcomm/robotcore/hardware/DcMotor$RunMode");
    this->c_zero_power_behavior = p_jni->FindClass("com/qualcomm/robotcore/hardware/DcMotor$ZeroPowerBehavior");
    this->c_angle_unit = p_jni->FindClass("org/firstinspires/ftc/robotcore/external/navigation/AngleUnit");

    this->m_setPower = p_jni->GetMethodID(clazz, "setPower", "(D)V");
    this->m_setDirection = p_jni->GetMethodID(clazz, "setDirection", "(Lcom/qualcomm/robotcore/hardware/DcMotorSimple$Direction;)V");
    this->m_setMode = p_jni->GetMethodID(clazz, "setMode", "(Lcom/qualcomm/robotcore/hardware/DcMotor$RunMode;)V");
    this->m_setZeroPowerBehavior = p_jni->GetMethodID(clazz, "setZeroPowerBehavior", "(Lcom/qualcomm/robotcore/hardware/DcMotor$ZeroPowerBehavior;)V");
    this->m_setTargetPosition = p_jni->GetMethodID(clazz, "setTargetPosition", "(I)V");
    this->m_setVelocity = p_jni->GetMethodID(clazz, "setVelocity", "(D)V");
    this->m_setVelocityWithUnit = p_jni->GetMethodID(clazz, "setVelocity", "(DLorg/firstinspires/ftc/robotcore/external/navigation/AngleUnit;)V");
    this->m_setVelocityPIDFCoefficients = p_jni->GetMethodID(clazz, "setVelocityPIDFCoefficients", "(DDDD)V");
    this->m_setPositionPIDFCoefficients = p_jni->GetMethodID(clazz, "setPositionPIDFCoefficients", "(D)V");

    this->m_getPower = p_jni->GetMethodID(clazz, "getPower", "()D");
    this->m_getDirection = p_jni->GetMethodID(clazz, "getDirection", "()Lcom/qualcomm/robotcore/hardware/DcMotorSimple$Direction;");
    this->m_getMode = p_jni->GetMethodID(clazz, "getMode", "()Lcom/qualcomm/robotcore/hardware/DcMotor$RunMode;");
    this->m_getZeroPowerBehavior = p_jni->GetMethodID(clazz, "getZeroPowerBehavior", "()Lcom/qualcomm/robotcore/hardware/DcMotor$ZeroPowerBehavior;");
    this->m_getTargetPosition = p_jni->GetMethodID(clazz, "getTargetPosition", "()I");
    this->m_getCurrentPosition = p_jni->GetMethodID(clazz, "getCurrentPosition", "()I");
    this->m_getVelocity = p_jni->GetMethodID(clazz, "getVelocity", "()D");
    this->m_getVelocityWithUnit = p_jni->GetMethodID(clazz, "getVelocity", "(Lorg/firstinspires/ftc/robotcore/external/navigation/AngleUnit;)D");
}

C_DcMotor::~C_DcMotor() {
    this->p_jni->DeleteLocalRef(this->self);
}

void C_DcMotor::setPower(double power) {
    this->p_jni->CallVoidMethod(this->self, this->m_setPower, power);
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

    jfieldID f_dir = this->p_jni->GetStaticFieldID(this->c_direction, fieldName.c_str(), "Lcom/qualcomm/robotcore/hardware/DcMotorSimple$Direction;");
    jobject j_dir = this->p_jni->GetStaticObjectField(this->c_direction, f_dir);

    this->p_jni->CallVoidMethod(this->self, this->m_setDirection, j_dir);
    this->p_jni->DeleteLocalRef(j_dir);
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

    jfieldID f_mode = this->p_jni->GetStaticFieldID(this->c_run_mode, fieldName.c_str(), "Lcom/qualcomm/robotcore/hardware/DcMotor$RunMode;");
    jobject j_mode = this->p_jni->GetStaticObjectField(this->c_run_mode, f_mode);

    this->p_jni->CallVoidMethod(this->self, this->m_setMode, j_mode);
    this->p_jni->DeleteLocalRef(j_mode);
}

void C_DcMotor::setZeroPowerBehavior(C_ZeroPowerBehavior zeroPowerBehavior) {
    std::string fieldName;

    switch (zeroPowerBehavior) {
        case UNKNOWN:
            fieldName = "UNKNOWN";
            break;
        case BRAKE:
            fieldName = "BRAKE";
            break;
        case FLOAT:
            fieldName = "FLOAT";
            break;
    }

    jfieldID f_zeroPowerBehavior = this->p_jni->GetStaticFieldID(this->c_zero_power_behavior, fieldName.c_str(), "Lcom/qualcomm/robotcore/hardware/DcMotor$ZeroPowerBehavior;");
    jobject j_zeroPowerBehavior = this->p_jni->GetStaticObjectField(this->c_zero_power_behavior, f_zeroPowerBehavior);

    this->p_jni->CallVoidMethod(this->self, this->m_setZeroPowerBehavior, j_zeroPowerBehavior);
    this->p_jni->DeleteLocalRef(j_zeroPowerBehavior);
}

void C_DcMotor::setTargetPosition(int targetPosition) {
    this->p_jni->CallVoidMethod(this->self, this->m_setTargetPosition, targetPosition);
}

void C_DcMotor::setVelocity(double velocity) {
    p_jni->CallVoidMethod(this->self, this->m_setVelocity, velocity);
}

void C_DcMotor::setVelocity(double velocity, C_AngleUnit unit) {
    std::string fieldName;

    switch (unit) {
        case RADIANS:
            fieldName = "RADIANS";
            break;
        case DEGREES:
            fieldName = "DEGREES";
            break;
    }

    jfieldID f_unit = this->p_jni->GetStaticFieldID(this->c_angle_unit, fieldName.c_str(), "Lcom/qualcomm/robotcore/hardware/DcMotor$RunMode;");
    jobject j_unit = this->p_jni->GetStaticObjectField(this->c_angle_unit, f_unit);

    this->p_jni->CallVoidMethod(this->self, this->m_setVelocityWithUnit, velocity, j_unit);
    this->p_jni->DeleteLocalRef(j_unit);
}

void C_DcMotor::setVelocityPIDFCoefficients(double p, double i, double d, double f) {
    p_jni->CallVoidMethod(this->self, this->m_setVelocityPIDFCoefficients, p, i, d, f);
}

void C_DcMotor::setPositionPIDFCoefficients(double p) {
    p_jni->CallVoidMethod(this->self, this->m_setPositionPIDFCoefficients, p);
}

double C_DcMotor::getPower() {
    return this->p_jni->CallDoubleMethod(this->self, this->m_getPower);
}

C_DcMotor::C_Direction C_DcMotor::getDirection() {
    jobject dir = this->p_jni->CallObjectMethod(this->self, this->m_getDirection);
    jmethodID m_name = this->p_jni->GetMethodID(this->c_direction, "name", "()Ljava/lang/String;");
    auto j_name = (jstring) this->p_jni->CallObjectMethod(dir, m_name);

    const char *c_str = this->p_jni->GetStringUTFChars(j_name, nullptr);
    auto dirName = std::string(c_str);

    this->p_jni->ReleaseStringUTFChars(j_name, c_str);
    this->p_jni->DeleteLocalRef(j_name);
    this->p_jni->DeleteLocalRef(dir);

    if (dirName == "REVERSE") return C_Direction::REVERSE;
    return C_Direction::FORWARD;
}

C_DcMotor::C_RunMode C_DcMotor::getMode() {
    jobject mode = this->p_jni->CallObjectMethod(this->self, this->m_getMode);
    jmethodID m_name = this->p_jni->GetMethodID(this->c_run_mode, "name", "()Ljava/lang/String;");
    auto j_name = (jstring) this->p_jni->CallObjectMethod(mode, m_name);

    const char *c_str = this->p_jni->GetStringUTFChars(j_name, nullptr);
    auto modeName = std::string(c_str);

    this->p_jni->ReleaseStringUTFChars(j_name, c_str);
    this->p_jni->DeleteLocalRef(j_name);
    this->p_jni->DeleteLocalRef(mode);

    if (modeName == "RUN_USING_ENCODER") return C_RunMode::RUN_USING_ENCODER;
    else if (modeName == "RUN_TO_POSITION") return C_RunMode::RUN_TO_POSITION;
    else if (modeName == "STOP_AND_RESET_ENCODER") return C_RunMode::STOP_AND_RESET_ENCODER;

    return C_RunMode::RUN_WITHOUT_ENCODER;
}

C_DcMotor::C_ZeroPowerBehavior C_DcMotor::getZeroPowerBehavior() {
    jobject zeroPowerBehavior = this->p_jni->CallObjectMethod(this->self, this->m_getZeroPowerBehavior);
    jmethodID m_name = this->p_jni->GetMethodID(this->c_zero_power_behavior, "name", "()Ljava/lang/String;");
    auto j_name = (jstring) this->p_jni->CallObjectMethod(zeroPowerBehavior, m_name);

    const char *c_str = this->p_jni->GetStringUTFChars(j_name, nullptr);
    auto zeroPowerBehaviorName = std::string(c_str);

    this->p_jni->ReleaseStringUTFChars(j_name, c_str);
    this->p_jni->DeleteLocalRef(j_name);
    this->p_jni->DeleteLocalRef(zeroPowerBehavior);

    if (zeroPowerBehaviorName == "BRAKE") return C_ZeroPowerBehavior::BRAKE;
    else if (zeroPowerBehaviorName == "UNKNOWN") return C_ZeroPowerBehavior::UNKNOWN;

    return C_ZeroPowerBehavior::FLOAT;
}

int C_DcMotor::getTargetPosition() {
    return this->p_jni->CallIntMethod(this->self, this->m_getTargetPosition);
}

int C_DcMotor::getCurrentPosition() {
    return this->p_jni->CallIntMethod(this->self, this->m_getCurrentPosition);
}

double C_DcMotor::getVelocity() {
    return this->p_jni->CallDoubleMethod(this->self, this->m_getVelocity);
}

double C_DcMotor::getVelocity(C_DcMotor::C_AngleUnit unit) {
    std::string fieldName;

    switch (unit) {
        case RADIANS:
            fieldName = "RADIANS";
            break;
        case DEGREES:
            fieldName = "DEGREES";
            break;
    }

    jfieldID f_unit = this->p_jni->GetStaticFieldID(this->c_angle_unit, fieldName.c_str(), "Lcom/qualcomm/robotcore/hardware/DcMotor$RunMode;");
    jobject j_unit = this->p_jni->GetStaticObjectField(this->c_angle_unit, f_unit);

    double velocity = this->p_jni->CallDoubleMethod(this->self, this->m_getVelocityWithUnit, j_unit);
    this->p_jni->DeleteLocalRef(j_unit);

    return velocity;
}