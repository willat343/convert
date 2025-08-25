#ifndef CONVERT_GTSAM_ROS_IMPL_NAVIGATION_NAV_MSGS_IMPL_HPP
#define CONVERT_GTSAM_ROS_IMPL_NAVIGATION_NAV_MSGS_IMPL_HPP

#include "convert/eigen_ros/geometry_msgs.hpp"
#include "convert/gtsam_ros/geometry_geometry_msgs.hpp"
#include "convert/gtsam_ros/impl/navigation_nav_msgs.hpp"
#include "convert/impl/convert.hpp"

namespace convert {

CONVERT_INLINE void to(const nav_msgs::Odometry& msg, gtsam::NavState& navstate) {
    gtsam::Pose3 pose;
    to(msg.pose.pose, pose);
    Eigen::Vector3d velocity;
    to(msg.twist.twist.linear, velocity);
    navstate = gtsam::NavState{pose, velocity};
}

}

#endif
