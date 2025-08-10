# SkiTag Firmware

This repository contains the C++ firmware for the SkiTag, a smart ski tracking device.

## Features

*   **Location Tracking:** Find your skis using the Android Find My network.
*   **Fitness Tracking:** (Future implementation) Track your ski activity, including speed, distance, and vertical descent.
*   **Ski Coach:** (Future implementation) Get real-time feedback on your technique.

## Hardware

The SkiTag firmware is designed to run on a custom PCB based on the Raspberry Pi RP2350 microcontroller.

### Components

*   **Microcontroller:** Raspberry Pi RP2350
*   **Bluetooth Module:** u-blox NINA-W102-00B
*   **IMU:** STMicroelectronics LSM6DSOXTR
*   **Buzzer:** Connected to GPIO 21

### Pinout

| Component         | Pin              | RP2350 Function |
| ----------------- | ---------------- | --------------- |
| **NINA-W102-00B** |                  |                 |
|                   | GPIO 8 (CS)      | SPI1_CSn        |
|                   | GPIO 9 (SCK)     | SPI1_SCK        |
|                   | GPIO 10 (MOSI)   | SPI1_TX         |
|                   | GPIO 11 (MISO)   | SPI1_RX         |
| **LSM6DSOXTR**    |                  |                 |
|                   | GPIO 12 (SDA)    | I2C0_SDA        |
|                   | GPIO 13 (SCL)    | I2C0_SCL        |
| **Buzzer**        | GPIO 21          | GPIO            |

## Building and Deployment

(Instructions to be added)
