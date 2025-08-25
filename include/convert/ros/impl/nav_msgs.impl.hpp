#ifndef CONVERT_ROS_IMPL_NAV_MSGS_IMPL_HPP
#define CONVERT_ROS_IMPL_NAV_MSGS_IMPL_HPP

#include "convert/impl/convert.hpp"
#include "convert/ros/geometry_msgs_nav_msgs.hpp"
#include "convert/ros/impl/nav_msgs.hpp"

// Helpers must be included last.
#include "convert/convert_helpers.hpp"

namespace convert {

CONVERT_INLINE void to(const std::vector<nav_msgs::Odometry>& from_msgs, nav_msgs::Path& to_msg) {
    const std::size_t size = from_msgs.size();
    to_msg.header = size == 0 ? std_msgs::Header() : from_msgs[0].header;
    to_msg.poses.resize(size);
    std::transform(from_msgs.cbegin(), from_msgs.cend(), to_msg.poses.begin(),
            [](const nav_msgs::Odometry& from_msg) { return to<geometry_msgs::PoseStamped>(from_msg); });
}

}

#endif
