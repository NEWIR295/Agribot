#include <ros/ros.h>
#include "AgribotCtrl.h"
geometry_msgs::Twist currentVelocity;
void cb(const geometry_msgs::Twist &vel){
  currentVelocity = vel;
}
/* Main function for AgriBOT node*/
int main(int argc, char** argv){
  ros::init(argc, argv, "AgribotVel");
  ros::NodeHandle n;
  ros::Publisher vel_pub = n.advertise<std_msgs::Float32MultiArray>("/AgribotVel", 50);
  ros::Subscriber vel_sub = n.subscribe("/Agribot_cmd_vel", 10, &cb);
  Agribot_ctrl agriBot;
  float wheel_separation;
  n.getParam("wheel_separation",wheel_separation);
  ros::Rate r(10.0);
  std_msgs::Float32MultiArray current_speed;
  ros::Time current_time, last_time;
  last_time = ros::Time::now();
  while(ros::ok()){
    current_time = ros::Time::now();// get time stamp of current message
    double dt = (current_time - last_time).toSec();   // time difference between now and last loop iteration
    //current_speed.data.clear(); // Clear previous data
    current_speed = agriBot.getLinearSpeed(currentVelocity,wheel_separation,dt);
    /* Publish the linear speed */
    if(!current_speed.data.empty())
      {
        //ROS_INFO("DONE");
        vel_pub.publish(current_speed); // publish linear speed for both motors to /myVel topic
      }
    else{
      vel_pub.publish(agriBot.stopAgribot());
      ROS_WARN("No data from cmd_vel topic.");
      continue;
    }
    /* Update the odometry */    
    last_time = current_time;/* Save time for next iteration */
    r.sleep();
    ros::spinOnce();               // check for incoming messages
   }
   return 0;
}