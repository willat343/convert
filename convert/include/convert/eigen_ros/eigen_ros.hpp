#ifndef CONVERT_EIGEN_ROS_EIGEN_ROS_HPP
#define CONVERT_EIGEN_ROS_EIGEN_ROS_HPP

#include <ros/ros.h>

#include <Eigen/Core>
#include <vector>

#include "convert/eigen_ros/geometry_msgs.hpp"
#include "convert/eigen_ros/std_msgs.hpp"

namespace convert {

/**
 * @brief Convert a boost::array to an Eigen::Matrix.
 * 
 * @tparam ArrayScalar 
 * @tparam Size 
 * @tparam Derived 
 * @param msg 
 * @param m 
 */
template<typename ArrayScalar, std::size_t Size, typename Derived>
void to(const boost::array<ArrayScalar, Size>& msg, Eigen::MatrixBase<Derived>& m);

/**
 * @brief Convert an Eigen::Matrix to a boost::array.
 * 
 * @tparam ArrayScalar 
 * @tparam Size 
 * @tparam Derived 
 * @param m 
 * @param msg 
 */
template<typename ArrayScalar, std::size_t Size, typename Derived>
void to(const Eigen::MatrixBase<Derived>& m, boost::array<ArrayScalar, Size>& msg);

}

#include "convert/eigen_ros/impl/eigen_ros.hpp"

#endif
