#ifndef CONVERT_ROS_IMPL_GEOMETRY_MSGS_NAV_MSGS_IMPL_HPP
#define CONVERT_ROS_IMPL_GEOMETRY_MSGS_NAV_MSGS_IMPL_HPP

#include "convert/impl/convert.hpp"
#include "convert/ros/impl/geometry_msgs_nav_msgs.hpp"

namespace convert {

CONVERT_INLINE void to(const nav_msgs::Odometry& from_msg, geometry_msgs::PoseStamped& to_msg) {
    to_msg.header = from_msg.header;
    to_msg.pose = from_msg.pose.pose;
}

}

#endif
