cmake_minimum_required(VERSION 3.19)
project(BalancingBeam)

set(CMAKE_CXX_STANDARD 17)

include_directories(fw_beam)

add_executable(BalancingBeam
        fw_beam/fw_beam.ino
        fw_beam/lp_filter.cpp
        fw_beam/lp_filter.h
        fw_beam/servo_handler.cpp
        fw_beam/servo_handler.h
        fw_beam/ultrasonic_handler.cpp
        fw_beam/ultrasonic_handler.h
        fw_beam/pid_control.cpp
        fw_beam/pid_control.h
        fw_beam/mpu6050.cpp
        fw_beam/mpu6050.h
        fw_beam/lcd_screen.cpp
        fw_beam/lcd_screen.h)
