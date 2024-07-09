#ifndef CONVERT_EIGEN_ROS_STD_MSGS_HPP
#define CONVERT_EIGEN_ROS_STD_MSGS_HPP

#include <std_msgs/Float64MultiArray.h>

#include <Eigen/Core>

namespace convert {

template<typename Derived>
void to(const Eigen::MatrixBase<Derived>& matrix, std_msgs::Float64MultiArray& msg);

template<typename Derived>
void to(const std_msgs::Float64MultiArray& msg, Eigen::MatrixBase<Derived>& matrix);

}

#include "convert/eigen_ros/impl/std_msgs.hpp"

#endif
