#ifndef CONVERT_EIGEN_ROS_GEOMETRY_MSGS_HPP
#define CONVERT_EIGEN_ROS_GEOMETRY_MSGS_HPP

#include <geometry_msgs/Point.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/Transform.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Vector3.h>

#include <Eigen/Core>
#include <Eigen/Geometry>

namespace convert {

void to(const Eigen::Isometry3d& transform, geometry_msgs::Transform& msg);

void to(const Eigen::Matrix3d& matrix, geometry_msgs::Quaternion& msg);

void to(const Eigen::Matrix4d& matrix, geometry_msgs::Pose& msg);

void to(const Eigen::Matrix4d& matrix, geometry_msgs::Transform& msg);

void to(const Eigen::Quaterniond& q, geometry_msgs::Quaternion& msg);

void to(const Eigen::Translation3d& v, geometry_msgs::Point& msg);

void to(const Eigen::Translation3d& v, geometry_msgs::Vector3& msg);

void to(const Eigen::Vector3d& v, geometry_msgs::Point& msg);

void to(const Eigen::Vector3d& v, geometry_msgs::Vector3& msg);

void to(const Eigen::Ref<const Eigen::Matrix<double, 6, 1>>& twist, geometry_msgs::Twist& msg);

void to(const geometry_msgs::Point& msg, Eigen::Ref<Eigen::Vector3d> v);

void to(const geometry_msgs::Point& msg, Eigen::Translation3d& v);

void to(const geometry_msgs::Pose& msg, Eigen::Ref<Eigen::Matrix4d> matrix);

void to(const geometry_msgs::Quaternion& msg, Eigen::Ref<Eigen::Matrix3d> matrix);

void to(const geometry_msgs::Quaternion& msg, Eigen::Quaterniond& q);

void to(const geometry_msgs::Transform& msg, Eigen::Isometry3d& transform);

void to(const geometry_msgs::Transform& msg, Eigen::Ref<Eigen::Matrix4d> matrix);

void to(const geometry_msgs::Vector3& msg, Eigen::Ref<Eigen::Vector3d> v);

void to(const geometry_msgs::Vector3& msg, Eigen::Translation3d& v);

void to(const geometry_msgs::Twist& msg, Eigen::Ref<Eigen::Matrix<double, 6, 1>> twist);

}

#endif
