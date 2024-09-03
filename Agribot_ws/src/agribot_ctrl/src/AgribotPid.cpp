#include <ros/ros.h>
#include "pid.h"

std_msgs::Float32MultiArray feedBack;
std_msgs::Float32MultiArray setpoint;

void enc_cb(const std_msgs::Float32MultiArray &wheel_ang_vel){
  feedBack = wheel_ang_vel;
}
void vel_cb(const std_msgs::Float32MultiArray &wheel_linear_vel){
  setpoint = wheel_linear_vel;
}

/* Main function for AgriBOT_PID node*/
int main(int argc, char** argv){
  ros::init(argc, argv, "AgribotPid");
  ros::NodeHandle n;
  ros::Publisher vel_pub = n.advertise<std_msgs::Float32MultiArray>("/AgribotVelWpid", 50);
  ros::Subscriber enc_sub = n.subscribe("/encoder", 10, &enc_cb);
  ros::Subscriber vel_sub = n.subscribe("/AgribotVel", 10, &vel_cb);
  float Kp_m1, Ki_m1, Kd_m1,Kp_m2, Ki_m2, Kd_m2,wheel_radius,max_vel;
  n.getParam("max_vel",max_vel);
  n.getParam("wheel_radius",wheel_radius);
  n.getParam("Kp_m1", Kp_m1);
  n.getParam("Ki_m1", Ki_m1);
  n.getParam("Kd_m1", Kd_m1);
  n.getParam("Kp_m2", Kp_m2);
  n.getParam("Ki_m2", Ki_m2);
  n.getParam("Kd_m2", Kd_m2);
  PIDController agriBot_m1(Kp_m1,Ki_m1,Kd_m1);
  PIDController agriBot_m2(Kp_m2,Ki_m2,Kd_m2);
  std_msgs::Float32MultiArray AgribotPwm;
  AgribotPwm.data.resize(2);
  ros::Rate r(10.0);
  ros::Time current_time, last_time;
  last_time = ros::Time::now();
  while(ros::ok()){
    current_time = ros::Time::now();// get time stamp of current message
    double dt = (current_time - last_time).toSec();   // time difference between now and last loop iteration
    AgribotPwm.data.clear(); // Clear previous data
    float error_m1, error_m2;
    // error_m1 = setpoint.data[0] - feedBack.data[0]*wheel_radius;
    // error_m2 = setpoint.data[1] - feedBack.data[1]*wheel_radius;
    if (setpoint.data.size() >= 2 && feedBack.data.size() >= 2) {
      error_m1 = setpoint.data[0] - feedBack.data[0] * wheel_radius;
      error_m2 = setpoint.data[1] - feedBack.data[1] * wheel_radius;
    } else {
      ROS_WARN("Insufficient data received from topics.");
      continue; // Skip this iteration of the loop
    }

    AgribotPwm.data[0]=agriBot_m1.compute(error_m1,max_vel,dt); //left motor pwm
    AgribotPwm.data[1]=agriBot_m2.compute(error_m2,max_vel,dt);//right motor pwm
    /* Check if the current_speed is empty or not */
    if (!AgribotPwm.data.empty()){
      /* If current_speed is not empty then publish linear speed for both motors to /myVel topic /AgribotVelWpid topic */
       vel_pub.publish(AgribotPwm);
    }else{
      ROS_INFO("Set Point is Empty!");
      continue;
    }
    /* Publish the calculated speed of both wheels on /AgribotVelWpid topic */
    last_time = current_time;/* Save time for next iteration */
    ros::spinOnce();               // check for incoming messages
    r.sleep();
    }
  return 0;
}
