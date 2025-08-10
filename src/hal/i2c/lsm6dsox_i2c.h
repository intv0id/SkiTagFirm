#ifndef LSM6DSOX_I2C_H
#define LSM6DSOX_I2C_H

#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define LSM6DSOX_I2C_ADDRESS 0x6A

class LSM6DSOX_I2C {
public:
    LSM6DSOX_I2C(i2c_inst_t *i2c, uint sda_pin, uint scl_pin);
    bool init();
    void read_raw_data(int16_t *accel, int16_t *gyro);

private:
    void write_register(uint8_t reg, uint8_t value);
    void read_registers(uint8_t reg, uint8_t *data, uint8_t len);

    i2c_inst_t *_i2c;
};

#endif // LSM6DSOX_I2C_H
