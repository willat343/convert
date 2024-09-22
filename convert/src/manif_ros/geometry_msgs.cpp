#include "convert/manif_ros/geometry_msgs.hpp"

#include <Eigen/Core>
#include <Eigen/Geometry>

#include "convert/eigen_ros/geometry_msgs.hpp"
// Helpers must be included last
#include "convert/convert_helpers.hpp"

namespace convert {

void to(const geometry_msgs::Point& msg, manif::R3d& r3d) {
    r3d = manif::R3d(to<Eigen::Vector3d>(msg));
}

void to(const geometry_msgs::Pose& msg, manif::R3d& r3d, manif::SO3d& so3d) {
    to(msg.position, r3d);
    to(msg.orientation, so3d);
}

void to(const geometry_msgs::Pose& msg, manif::SE3d& se3d) {
    se3d = manif::SE3d(to<Eigen::Vector3d>(msg.position), to<Eigen::Quaterniond>(msg.orientation));
}

void to(const geometry_msgs::Transform& msg, manif::SE3d& se3d) {
    se3d = manif::SE3d(to<Eigen::Vector3d>(msg.translation), to<Eigen::Quaterniond>(msg.rotation));
}

void to(const geometry_msgs::Transform& msg, manif::R3d& r3d, manif::SO3d& so3d) {
    to(msg.translation, r3d);
    to(msg.rotation, so3d);
}

void to(const geometry_msgs::Quaternion& msg, manif::SO3d& so3d) {
    so3d = manif::SO3d(to<Eigen::Quaterniond>(msg));
}

void to(const geometry_msgs::Vector3& msg, manif::R3d& r3d) {
    r3d = manif::R3d(to<Eigen::Vector3d>(msg));
}

void to(const manif::SE3d& se3d, geometry_msgs::Pose& msg) {
    to(se3d.translation(), msg.position);
    to(se3d.rotation(), msg.orientation);
}

void to(const manif::SE3d& se3d, geometry_msgs::Transform& msg) {
    to(se3d.translation(), msg.translation);
    to(se3d.rotation(), msg.rotation);
}

void to(const manif::SO3d& so3d, geometry_msgs::Quaternion& msg) {
    msg = to<geometry_msgs::Quaternion>(so3d.quat());
}

void to(const manif::R3d& r3d, geometry_msgs::Point& msg) {
    msg = to<geometry_msgs::Point>(r3d.log().coeffs());
}

void to(const manif::R3d& r3d, geometry_msgs::Vector3& msg) {
    msg = to<geometry_msgs::Vector3>(r3d.log().coeffs());
}

void to(const manif::R3d& r3d, const manif::SO3d& so3d, geometry_msgs::Pose& msg) {
    to(r3d, msg.position);
    to(so3d, msg.orientation);
}

void to(const manif::R3d& r3d, const manif::SO3d& so3d, geometry_msgs::Transform& msg) {
    to(r3d, msg.translation);
    to(so3d, msg.rotation);
}

}
