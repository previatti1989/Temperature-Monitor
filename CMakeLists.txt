cmake_minimum_required(VERSION 3.10)

# Project Name
project(TemperatureMonitor C)

# Set C Standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Add the source files
add_executable(TemperatureMonitor
    main.c
    system_config.c
    adc_handler.c
    led_controller.c
    eeprom_handler.c
)

# Include Directories
include_directories(${CMAKE_SOURCE_DIR})