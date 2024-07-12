#ifndef CONVERT_GTSAM_ROS_GEOMETRY_GEOMETRY_MSGS_HPP
#define CONVERT_GTSAM_ROS_GEOMETRY_GEOMETRY_MSGS_HPP

#include <gtsam/geometry/Pose3.h>
#include <gtsam/geometry/Rot3.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Quaternion.h>

namespace convert {

void to(const geometry_msgs::Pose& msg, gtsam::Pose3& pose);

void to(const geometry_msgs::Quaternion& msg, gtsam::Rot3& r);

}

#endif
