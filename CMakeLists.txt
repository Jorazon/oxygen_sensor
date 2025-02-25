cmake_minimum_required(VERSION 3.10)
project(EOxygenSensor)

include_directories(./include)

add_executable(${PROJECT_NAME} main.c ${PROJECT_NAME}.c)

target_link_libraries(${PROJECT_NAME} i2c)
