cmake_minimum_required(VERSION 3.10)
project(EOxygenSensor)
file(WRITE ${CMAKE_BINARY_DIR}/.gitignore "*")

include_directories(./include)
add_subdirectory(src)

set(EXE_NAME i2coxygen)
add_executable(${EXE_NAME} main.c)

target_link_libraries(${EXE_NAME} delay EOxygenSensor)
