#include "lsm6dsox_i2c.h"
#include "pico/stdlib.h"

// Register addresses
#define LSM6DSOX_WHO_AM_I_REG 0x0F
#define LSM6DSOX_CTRL1_XL_REG 0x10
#define LSM6DSOX_CTRL2_G_REG  0x11
#define LSM6DSOX_OUTX_L_G_REG 0x22

LSM6DSOX_I2C::LSM6DSOX_I2C(i2c_inst_t *i2c, uint sda_pin, uint scl_pin) : _i2c(i2c) {
    i2c_init(_i2c, 400 * 1000); // 400kHz
    gpio_set_function(sda_pin, GPIO_FUNC_I2C);
    gpio_set_function(scl_pin, GPIO_FUNC_I2C);
    gpio_pull_up(sda_pin);
    gpio_pull_up(scl_pin);
}

bool LSM6DSOX_I2C::init() {
    uint8_t who_am_i;
    read_registers(LSM6DSOX_WHO_AM_I_REG, &who_am_i, 1);

    if (who_am_i != 0x6C) {
        return false;
    }

    // Configure accelerometer: 104Hz, 2g
    write_register(LSM6DSOX_CTRL1_XL_REG, 0x40);

    // Configure gyroscope: 104Hz, 250dps
    write_register(LSM6DSOX_CTRL2_G_REG, 0x40);

    return true;
}

void LSM6DSOX_I2C::read_raw_data(int16_t *accel, int16_t *gyro) {
    uint8_t data[12];
    read_registers(LSM6DSOX_OUTX_L_G_REG, data, 12);

    gyro[0] = (data[1] << 8) | data[0];
    gyro[1] = (data[3] << 8) | data[2];
    gyro[2] = (data[5] << 8) | data[4];

    accel[0] = (data[7] << 8) | data[6];
    accel[1] = (data[9] << 8) | data[8];
    accel[2] = (data[11] << 8) | data[10];
}

void LSM6DSOX_I2C::write_register(uint8_t reg, uint8_t value) {
    uint8_t data[] = {reg, value};
    i2c_write_blocking(_i2c, LSM6DSOX_I2C_ADDRESS, data, 2, false);
}

void LSM6DSOX_I2C::read_registers(uint8_t reg, uint8_t *data, uint8_t len) {
    i2c_write_blocking(_i2c, LSM6DSOX_I2C_ADDRESS, &reg, 1, true);
    i2c_read_blocking(_i2c, LSM6DSOX_I2C_ADDRESS, data, len, false);
}
