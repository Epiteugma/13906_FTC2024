
cmake_minimum_required(VERSION 3.22.1)

project("teamcode")

add_library(teamcode SHARED
        lib/c_op_mode.cpp
        lib/c_gamepad.cpp
        lib/c_telemetry.cpp
        lib/hardware/c_hardware_map.cpp
        lib/hardware/c_dc_motor.cpp
        lib/hardware/c_servo.cpp
        lib/hardware/c_touchsensor.cpp

        utils/utils.cpp
        utils/maths.cpp
        utils/kinematics/drivetrain.cpp
        utils/odometry/odometry.cpp
        utils/control/pid.cpp

        opmodes/drive.cpp
        opmodes/servo_tuner.cpp

        opmodes/auton.cpp
        opmodes/auton_place.cpp
        opmodes/auton_park.cpp

        robot.cpp
)

target_include_directories(teamcode PRIVATE .)

target_link_libraries(teamcode
    android
    log)
