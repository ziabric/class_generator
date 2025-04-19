cmake_minimum_required(VERSION 3.10)

project(class_generator)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

file(
    GLOB
    THIRDPARTY_FILES
    "thirdparty/*.hxx"
)

file(
    GLOB
    INTERNAL_FILES
    "internal/*.h"
    "internal/*.hpp"
)

file(
    GLOB
    GENERATOR_FILES
    "generator/*.hpp"
)

add_executable(
    ${PROJECT_NAME}
    ${THIRDPARTY_FILES}
    "main.cpp"
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    "."
)
