#ifndef CONVERT_SENSORBOX_ROS_POSE_HPP
#define CONVERT_SENSORBOX_ROS_POSE_HPP

#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TransformStamped.h>

#include <sensorbox/pose.hpp>

namespace convert {

void to(const geometry_msgs::PoseStamped& msg, sensorbox::PoseMeasurement<3>& pose);

void to(const sensorbox::PoseMeasurement<3>& pose, geometry_msgs::PoseStamped& msg);

void to(const geometry_msgs::TransformStamped& msg, sensorbox::PoseMeasurement<3>& pose);

void to(const sensorbox::PoseMeasurement<3>& pose, geometry_msgs::TransformStamped& msg);

}

#endif
