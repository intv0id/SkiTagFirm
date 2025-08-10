#ifndef KALMAN_H
#define KALMAN_H

class Kalman {
public:
    Kalman();
    float update(float newAngle, float newRate, float dt);
    float getAngle() const { return _angle; }

private:
    float Q_angle; // Process noise variance for the accelerometer
    float Q_bias;  // Process noise variance for the gyro bias
    float R_measure; // Measurement noise variance - this is actually the variance of the measurement noise

    float _angle; // The angle in degrees
    float bias;  // The gyro bias in degrees/sec
    float P[2][2]; // Error covariance matrix
};

#endif // KALMAN_H
