#ifndef CONVERT_GTSAM_ROS_IMPL_GEOMETRY_GEOMETRY_MSGS_IMPL_HPP
#define CONVERT_GTSAM_ROS_IMPL_GEOMETRY_GEOMETRY_MSGS_IMPL_HPP

#include "convert/eigen_ros/geometry_msgs.hpp"
#include "convert/gtsam_ros/impl/geometry_geometry_msgs.hpp"
#include "convert/impl/convert.hpp"

namespace convert {

CONVERT_INLINE void to(const geometry_msgs::Pose& msg, gtsam::Pose3& pose) {
    Eigen::Matrix4d p;
    to(msg, p);
    pose = gtsam::Pose3{p};
}

CONVERT_INLINE void to(const geometry_msgs::Quaternion& msg, gtsam::Rot3& r) {
    Eigen::Quaterniond q;
    to(msg, q);
    r = gtsam::Rot3{q};
}

CONVERT_INLINE void to(const geometry_msgs::Transform& msg, gtsam::Pose3& pose) {
    Eigen::Matrix4d p;
    to(msg, p);
    pose = gtsam::Pose3{p};
}

}

#endif
