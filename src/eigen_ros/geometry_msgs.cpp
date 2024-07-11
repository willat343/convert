#include "convert/eigen_ros/geometry_msgs.hpp"

#include "convert/eigen_ros/eigen_ros.hpp"

namespace convert {

void to(const Eigen::Isometry3d& transform, geometry_msgs::Transform& msg) {
    to(transform.translation(), msg.translation);
    to(Eigen::Quaterniond(transform.rotation()), msg.rotation);
}

void to(const Eigen::Matrix3d& matrix, geometry_msgs::Quaternion& msg) {
    Eigen::Quaterniond q{matrix};
    to(q, msg);
}

void to(const Eigen::Matrix4d& matrix, geometry_msgs::Pose& msg) {
    to(matrix.block<3, 1>(0, 3), msg.position);
    to(matrix.block<3, 3>(3, 3), msg.orientation);
}

void to(const Eigen::Matrix4d& matrix, geometry_msgs::Transform& msg) {
    to(matrix.block<3, 1>(0, 3), msg.translation);
    to(matrix.block<3, 3>(3, 3), msg.rotation);
}

void to(const Eigen::Quaterniond& q, geometry_msgs::Quaternion& msg) {
    // no q.normalize() to prevent obscuring real issues
    msg.w = q.w();
    msg.x = q.x();
    msg.y = q.y();
    msg.z = q.z();
}

void to(const Eigen::Translation3d& v, geometry_msgs::Point& msg) {
    msg.x = v.x();
    msg.y = v.y();
    msg.z = v.z();
}

void to(const Eigen::Translation3d& v, geometry_msgs::Vector3& msg) {
    msg.x = v.x();
    msg.y = v.y();
    msg.z = v.z();
}

void to(const Eigen::Vector3d& v, geometry_msgs::Point& msg) {
    msg.x = v[0];
    msg.y = v[1];
    msg.z = v[2];
}

void to(const Eigen::Vector3d& v, geometry_msgs::Vector3& msg) {
    msg.x = v[0];
    msg.y = v[1];
    msg.z = v[2];
}

void to(const Eigen::Ref<const Eigen::Matrix<double, 6, 1>>& twist, geometry_msgs::Twist& msg) {
    // TODO: find a way around using eval() here (Eigen::Ref causes ambiguity)
    to(twist.head<3>().eval(), msg.linear);
    to(twist.tail<3>().eval(), msg.angular);
}

void to(const geometry_msgs::Point& msg, Eigen::Ref<Eigen::Vector3d> v) {
    v[0] = msg.x;
    v[1] = msg.y;
    v[2] = msg.z;
}

void to(const geometry_msgs::Point& msg, Eigen::Translation3d& v) {
    v.x() = msg.x;
    v.y() = msg.y;
    v.z() = msg.z;
}

void to(const geometry_msgs::Pose& msg, Eigen::Ref<Eigen::Matrix4d> matrix) {
    to(msg.position, matrix.block<3, 1>(0, 3));
    to(msg.orientation, matrix.block<3, 3>(0, 0));
    matrix.block<1, 3>(3, 0) = Eigen::RowVector3d::Zero();
    matrix(3, 3) = 1.0;
}

void to(const geometry_msgs::Quaternion& msg, Eigen::Ref<Eigen::Matrix3d> matrix) {
    Eigen::Quaterniond q;
    to(msg, q);
    matrix = q.matrix();
}

void to(const geometry_msgs::Quaternion& msg, Eigen::Quaterniond& q) {
    q.w() = msg.w;
    q.x() = msg.x;
    q.y() = msg.y;
    q.z() = msg.z;
    // no q.normalize() to prevent obscuring real issues
}

void to(const geometry_msgs::Transform& msg, Eigen::Isometry3d& transform) {
    Eigen::Translation3d t;
    to(msg.translation, t);
    Eigen::Quaterniond q;
    to(msg.rotation, q);
    transform = t * q;
}

void to(const geometry_msgs::Transform& msg, Eigen::Ref<Eigen::Matrix4d> matrix) {
    to(msg.translation, matrix.block<3, 1>(0, 3));
    to(msg.rotation, matrix.block<3, 3>(0, 0));
    matrix.block<1, 3>(3, 0) = Eigen::RowVector3d::Zero();
    matrix(3, 3) = 1.0;
}

void to(const geometry_msgs::Vector3& msg, Eigen::Ref<Eigen::Vector3d> v) {
    v[0] = msg.x;
    v[1] = msg.y;
    v[2] = msg.z;
}

void to(const geometry_msgs::Vector3& msg, Eigen::Translation3d& v) {
    v.x() = msg.x;
    v.y() = msg.y;
    v.z() = msg.z;
}

void to(const geometry_msgs::Twist& msg, Eigen::Ref<Eigen::Matrix<double, 6, 1>> twist) {
    to(msg.linear, twist.head<3>());
    to(msg.angular, twist.tail<3>());
}

}
