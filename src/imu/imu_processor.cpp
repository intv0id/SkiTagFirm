#include "imu_processor.h"
#include <math.h>
#include "pico/stdlib.h"

#define RAD_TO_DEG 57.295779513082320876798154814105

IMUProcessor::IMUProcessor(LSM6DSOX_I2C &imu) : _imu(imu) {
    _last_update_time = time_us_32();
}

void IMUProcessor::process() {
    int16_t accel[3], gyro[3];
    _imu.read_raw_data(accel, gyro);

    // Calculate pitch and roll from accelerometer data
    float roll = atan2(accel[1], accel[2]) * RAD_TO_DEG;
    float pitch = atan2(-accel[0], sqrt(accel[1] * accel[1] + accel[2] * accel[2])) * RAD_TO_DEG;

    // Calculate delta time
    uint32_t now = time_us_32();
    float dt = (now - _last_update_time) / 1000000.0f;
    _last_update_time = now;

    // Apply Kalman filter
    // Note: Gyro data needs to be scaled correctly
    float gyroX = gyro[0] / 131.0; // For 250 dps sensitivity
    float gyroY = gyro[1] / 131.0;

    _kalmanX.update(pitch, gyroX, dt);
    _kalmanY.update(roll, gyroY, dt);
}

float IMUProcessor::getPitch() {
    return _kalmanX.getAngle();
}

float IMUProcessor::getRoll() {
    return _kalmanY.getAngle();
}
