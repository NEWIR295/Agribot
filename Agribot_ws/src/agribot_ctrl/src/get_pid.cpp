#include <ros/ros.h>
#include "pid.h"
#include <std_msgs/Float32.h>

std_msgs::Float32 feedBack;

void enc_cb(const std_msgs::Float32 &wheel_ang_vel) {
    feedBack = wheel_ang_vel;
}

/* Main function for AgriBOT_PID node*/
int main(int argc, char** argv) {
    ros::init(argc, argv, "getPid");
    ros::NodeHandle n;
    ros::Publisher vel_pub = n.advertise<std_msgs::Float32>("/AgribotVelWpid", 50);
    ros::Subscriber enc_sub = n.subscribe("/encoder", 10, &enc_cb);

    float motor_speed;

    PIDController agriBot_m1(0.0, 0.0, 0.0); // Initialize with dummy values

    std_msgs::Float32 AgribotPwm;
    float Kp, Ki, Kd, max_vel;
    n.getParam("/motor_reconfigure/motor_speed", motor_speed);
    n.getParam("/motor_reconfigure/P", Kp);
    n.getParam("/motor_reconfigure/I", Ki);
    n.getParam("/motor_reconfigure/D", Kd);
    n.getParam("/max_vel", max_vel);
    ros::Rate r(10.0);
    ros::Time current_time, last_time;
    last_time = ros::Time::now();

    while (ros::ok()) {
        // Update parameters each loop iteration
        n.getParam("/motor_reconfigure/motor_speed", motor_speed);
        n.getParam("/motor_reconfigure/P", Kp);
        n.getParam("/motor_reconfigure/I", Ki);
        n.getParam("/motor_reconfigure/D", Kd);
        
        agriBot_m1.setParameters(Kp, Ki, Kd); // Update PID constants

        current_time = ros::Time::now(); // Get time stamp of current message
        double dt = (current_time - last_time).toSec(); // Time difference between now and last loop iteration

        float error_m1 = motor_speed - feedBack.data;
        AgribotPwm.data = agriBot_m1.compute(error_m1, max_vel, dt); // Left motor pwm

        vel_pub.publish(AgribotPwm); // Publish linear speed for both motors to /AgribotVelWpid topic

        last_time = current_time; // Save time for next iteration
        ros::spinOnce(); // Check for incoming messages
        r.sleep();
    }
    
    return 0;
}
