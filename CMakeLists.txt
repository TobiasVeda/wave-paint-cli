cmake_minimum_required(VERSION 4.1)
project(wave)

set(CMAKE_CXX_STANDARD 20)

add_executable(wave main.cpp
        Utils.h
        Terminal.cpp
        Terminal.h
        Process.cpp
        Process.h
        Brush.cpp
        Brush.h
        Keymap.cpp
        Keymap.h
)
