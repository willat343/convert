#ifndef CONVERT_SENSORBOX_ROS_POSE_TWIST_HPP
#define CONVERT_SENSORBOX_ROS_POSE_TWIST_HPP

#include <nav_msgs/Odometry.h>

#include <sensorbox/pose_twist.hpp>

namespace convert {

void to(const nav_msgs::Odometry& msg, sensorbox::PoseTwistMeasurement<3>& pose_twist);

void to(const sensorbox::PoseTwistMeasurement<3>& pose_twist, nav_msgs::Odometry& msg);

}

#endif
