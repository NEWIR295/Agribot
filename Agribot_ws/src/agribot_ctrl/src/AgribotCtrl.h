#ifndef AGRIBOT_CTRL_H
#define AGRIBOT_CTRL_H
#include <tf/transform_broadcaster.h>
#include "geometry_msgs/Twist.h"
#include "nav_msgs/Odometry.h"
#include "std_msgs/Float32MultiArray.h"
#include <Eigen/Dense>
#include <cmath>

using namespace Eigen;

class Agribot_ctrl {
private:

    Matrix<float, 2, 3> matrix1_i;
    Matrix<float, 3, 1> matrix2_i;
    Matrix<float, 3, 2> matrix1_f;
    Matrix<float, 2, 1> matrix2_f;
    double theta_initial;
    double x_initial;
    double y_initial;
public:
    Agribot_ctrl();
    std_msgs::Float32MultiArray stopAgribot();
    std_msgs::Float32MultiArray getLinearSpeed(const geometry_msgs::Twist &cmdVel,float wheel_separation,float dt);
    nav_msgs::Odometry distance_covered_enc(float dt, float w_l, float w_r,float wheel_radius,float wheel_separation,ros::Time current_time);
    geometry_msgs::Twist cmdVel(float w_l, float w_r,float wheel_radius,float wheel_separation) ;

    ~Agribot_ctrl();
};

#endif // AGRIBOT_CTRL_H
