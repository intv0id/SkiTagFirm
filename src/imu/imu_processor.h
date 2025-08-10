#ifndef IMU_PROCESSOR_H
#define IMU_PROCESSOR_H

#include "lsm6dsox_i2c.h"
#include "kalman.h"

class IMUProcessor {
public:
    IMUProcessor(LSM6DSOX_I2C &imu);
    void process();
    float getPitch();
    float getRoll();

private:
    LSM6DSOX_I2C &_imu;
    Kalman _kalmanX;
    Kalman _kalmanY;
    uint32_t _last_update_time;
};

#endif // IMU_PROCESSOR_H
