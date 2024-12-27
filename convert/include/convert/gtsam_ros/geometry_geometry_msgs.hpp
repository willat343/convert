#ifndef CONVERT_GTSAM_ROS_GEOMETRY_GEOMETRY_MSGS_HPP
#define CONVERT_GTSAM_ROS_GEOMETRY_GEOMETRY_MSGS_HPP

#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/Transform.h>
#include <gtsam/geometry/Pose3.h>
#include <gtsam/geometry/Rot3.h>

namespace convert {

void to(const geometry_msgs::Pose& msg, gtsam::Pose3& pose);

void to(const geometry_msgs::Quaternion& msg, gtsam::Rot3& r);

void to(const geometry_msgs::Transform& msg, gtsam::Pose3& pose);

}

#endif
