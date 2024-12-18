
cmake_minimum_required(VERSION 3.22.1)

project("team_code")

add_library(team_code SHARED
        lib/c_op_mode.cpp
        opmodes/native.cpp
)

target_link_libraries(team_code
    android
    log)
