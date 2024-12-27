#include "convert/gtsam_ros/geometry_geometry_msgs.hpp"

#include "convert/eigen_ros/geometry_msgs.hpp"

namespace convert {

void to(const geometry_msgs::Pose& msg, gtsam::Pose3& pose) {
    Eigen::Matrix4d p;
    to(msg, p);
    pose = gtsam::Pose3{p};
}

void to(const geometry_msgs::Quaternion& msg, gtsam::Rot3& r) {
    Eigen::Quaterniond q;
    to(msg, q);
    r = gtsam::Rot3{q};
}

void to(const geometry_msgs::Transform& msg, gtsam::Pose3& pose) {
    Eigen::Matrix4d p;
    to(msg, p);
    pose = gtsam::Pose3{p};
}

}
