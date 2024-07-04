#ifndef CONVERT_ROS_NAV_MSGS_HPP
#define CONVERT_ROS_NAV_MSGS_HPP

#include <nav_msgs/Odometry.h>
#include <nav_msgs/Path.h>

#include <vector>

namespace convert {

/**
 * @brief Convert `nav_msgs::Odometry` messages to `nav_msgs::Path`.
 *
 * @param from_msg
 * @param to_msg
 */
void to(const std::vector<nav_msgs::Odometry>& from_msg, nav_msgs::Path& to_msg);

}

#endif
