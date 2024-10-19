cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(pico_i2c_device)
# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add the source file for the library
add_library(pico_i2c_device STATIC i2c_device.cpp)

# Link the necessary libraries from the Pico SDK
target_link_libraries(pico_i2c_device
        pico_stdlib     # Standard Pico libraries
        hardware_i2c    # The hardware_pwm library
)
# Add the standard include files
target_include_directories(pico_i2c_device PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)