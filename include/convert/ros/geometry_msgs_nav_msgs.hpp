#ifndef CONVERT_ROS_GEOMETRY_MSGS_NAV_MSGS_HPP
#define CONVERT_ROS_GEOMETRY_MSGS_NAV_MSGS_HPP

#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/Odometry.h>
#include <nav_msgs/Path.h>

namespace convert {

/**
 * @brief Convert `nav_msgs::Odometry` to `geometry_msgs::PoseStamped`.
 *
 * Warning: Pose covariance, twist, and twist covariance information is lost.
 *
 * @param from_msg
 * @param to_msg
 */
void to(const nav_msgs::Odometry& from_msg, geometry_msgs::PoseStamped& to_msg);

}

#include "convert/ros/impl/geometry_msgs_nav_msgs.hpp"

#endif
