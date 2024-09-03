#ifndef AGRIBOT_PID
#define AGRIBOT_PID

#include "std_msgs/Float32MultiArray.h"

class PIDController {
private:
    // PID gains
    float Kp;
    float Ki;
    float Kd;
    // Previous error and integral term
    float prev_error = 0;
    float integral = 0;
    float derivative = 0;
public:
    // PID Constructor
    PIDController(float Kp, float Ki, float Kd);
    // Method to update PID parameters
    void setParameters(float Kp, float Ki, float Kd);
    // Compute the optimized output
    float compute(float error, float max_vel, double dt);
};

#endif // AGRIBOT_PID
