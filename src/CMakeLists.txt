include_directories(../include)
add_library(delay STATIC delay.c)
add_library(EOxygenSensor STATIC EOxygenSensor.c)
target_link_libraries(EOxygenSensor i2c)