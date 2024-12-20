
cmake_minimum_required(VERSION 3.22.1)

project("teamcode")

add_library(teamcode SHARED
        lib/c_op_mode.cpp
        lib/c_gamepad.cpp
        lib/c_telemetry.cpp
        lib/hardware/c_hardware_map.cpp
        lib/hardware/c_dc_motor.cpp
        lib/hardware/c_servo.cpp

        opmodes/drive.cpp
)

target_link_libraries(teamcode
    android
    log)
