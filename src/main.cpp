#include <stdio.h>
#include "pico/stdlib.h"
#include "buzzer.h"
#include "lsm6dsox_i2c.h"
#include "nina_spi.h"
#include "find_my.h"
#include "imu_processor.h"

// Pin definitions
#define BUZZER_PIN 21
#define NINA_CS_PIN 8
#define NINA_SCK_PIN 9
#define NINA_MOSI_PIN 10
#define NINA_MISO_PIN 11
#define LSM6DSOX_SDA_PIN 12
#define LSM6DSOX_SCL_PIN 13

int main() {
    stdio_init_all();

    // Initialize drivers
    Buzzer buzzer(BUZZER_PIN);
    LSM6DSOX_I2C imu_driver(i2c0, LSM6DSOX_SDA_PIN, LSM6DSOX_SCL_PIN);
    NINA_SPI nina(spi1, NINA_MISO_PIN, NINA_MOSI_PIN, NINA_SCK_PIN, NINA_CS_PIN);
    FindMy find_my(nina);
    IMUProcessor imu_processor(imu_driver);

    // Initialize hardware
    if (!imu_driver.init()) {
        printf("IMU initialization failed!\\n");
        while (true);
    }

    if (!nina.init()) {
        printf("NINA module initialization failed!\\n");
        while (true);
    }

    if (!find_my.init()) {
        printf("FindMy initialization failed!\\n");
        while(true);
    }

    printf("SkiTag initialized!\\n");

    while (true) {
        // Process IMU data
        imu_processor.process();

        // Update BLE characteristic
        find_my.update_orientation(imu_processor.getPitch(), imu_processor.getRoll());

        // Process BLE events
        find_my.process();

        sleep_ms(10);
    }

    return 0;
}
