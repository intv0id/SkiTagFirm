cmake_minimum_required(VERSION 3.13)

# Pull in Raspberry Pi Pico SDK
# This will be cloned into the build directory
include(pico_sdk_import.cmake)

project(skitag_firmware VERSION 0.1.0 C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Pass version to the code
target_compile_definitions(skitag_firmware PUBLIC "FIRMWARE_VERSION=\\"${PROJECT_VERSION}\\"")

# Initializes the Pico SDK
pico_sdk_init()

# Add executable
add_executable(skitag_firmware
    src/main.cpp
    src/hal/gpio/buzzer.cpp
    src/hal/i2c/lsm6dsox_i2c.cpp
    src/hal/spi/nina_spi.cpp
    src/ble/find_my.cpp
    src/imu/imu_processor.cpp
    src/kalman/kalman.cpp
)

# Add include directories
target_include_directories(skitag_firmware PUBLIC
    src/hal/gpio
    src/hal/i2c
    src/hal/spi
    src/ble
    src/imu
    src/kalman
)

# Add the Pico SDK libraries
target_link_libraries(skitag_firmware pico_stdlib hardware_spi hardware_i2c)

# Enable usb output, disable uart output
pico_enable_stdio_usb(skitag_firmware 1)
pico_enable_stdio_uart(skitag_firmware 0)

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(skitag_firmware)
