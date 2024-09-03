#include "pid.h"

// PID Constructor
PIDController::PIDController(float Kp, float Ki, float Kd) {
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
}

// Method to update PID parameters
void PIDController::setParameters(float Kp, float Ki, float Kd) {
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
}

// Compute the optimized output
float PIDController::compute(float error, float max_vel, double dt) {
    // Update integral term with anti-windup
    float integral_term = integral + (error * dt);
    if (integral_term < -max_vel / Ki)
        integral = -max_vel / Ki;
    else if (integral_term > max_vel / Ki)
        integral = max_vel / Ki;
    else
        integral = integral_term;

    // Low-pass filter for derivative term to prevent derivative kick
    float derivative_term = (error - prev_error) / dt;
    derivative = 0.8 * derivative + 0.2 * derivative_term;

    // Compute PID output
    float outputLinearVelocity = Kp * error + Ki * integral + Kd * derivative;

    // Convert output speed to PWM with saturation handling
    int m_pwm = round((outputLinearVelocity * 255) / max_vel);
    m_pwm = std::min(std::max(m_pwm, -255), 255); // Clamp within [-255, 255] range

    // Update previous error
    prev_error = error;

    return m_pwm;
}
