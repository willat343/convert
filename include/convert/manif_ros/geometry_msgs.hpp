#ifndef CONVERT_MANIF_ROS_GEOMETRY_MSGS_HPP
#define CONVERT_MANIF_ROS_GEOMETRY_MSGS_HPP

#include <geometry_msgs/Point.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/Transform.h>
#include <geometry_msgs/Vector3.h>
#include <manif/Rn.h>
#include <manif/SE3.h>
#include <manif/SO3.h>

namespace convert {

void to(const geometry_msgs::Point& msg, manif::R3d& r3d);

void to(const geometry_msgs::Pose& msg, manif::R3d& r3d, manif::SO3d& so3d);

void to(const geometry_msgs::Pose& msg, manif::SE3d& se3d);

void to(const geometry_msgs::Transform& msg, manif::SE3d& se3d);

void to(const geometry_msgs::Transform& msg, manif::R3d& r3d, manif::SO3d& so3d);

void to(const geometry_msgs::Quaternion& msg, manif::SO3d& so3d);

void to(const geometry_msgs::Vector3& msg, manif::R3d& r3d);

void to(const manif::SE3d& se3d, geometry_msgs::Pose& msg);

void to(const manif::SE3d& se3d, geometry_msgs::Transform& msg);

void to(const manif::SO3d& so3d, geometry_msgs::Quaternion& msg);

void to(const manif::R3d& r3d, geometry_msgs::Point& msg);

void to(const manif::R3d& r3d, geometry_msgs::Vector3& msg);

void to(const manif::R3d& r3d, const manif::SO3d& so3d, geometry_msgs::Pose& msg);

void to(const manif::R3d& r3d, const manif::SO3d& so3d, geometry_msgs::Transform& msg);

}

#endif
