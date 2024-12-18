
cmake_minimum_required(VERSION 3.22.1)

project("team_code")

add_library(team_code SHARED
        lib/c_op_mode.cpp
        lib/c_gamepad.cpp
        lib/c_hardware_map.cpp
        lib/c_dc_motor.cpp
        lib/c_servo.cpp
        opmodes/native.cpp
)

target_link_libraries(team_code
    android
    log)
