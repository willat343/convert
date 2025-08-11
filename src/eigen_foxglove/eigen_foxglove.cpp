#include "convert/eigen_foxglove/eigen_foxglove.hpp"

namespace convert {

void to(const Eigen::Ref<const Eigen::Vector3d>& in, foxglove::schemas::Vector3& out) {
    out.x = in[0];
    out.y = in[1];
    out.z = in[2];
}

void to(const Eigen::Ref<const Eigen::Vector2d>& in, foxglove::schemas::Vector2& out) {
    out.x = in[0];
    out.y = in[1];
}

void to(const Eigen::Ref<const Eigen::Vector2d>& in, foxglove::schemas::Vector3& out) {
    out.x = in[0];
    out.y = in[1];
    out.z = 0.0;
}

void to(const Eigen::Ref<const Eigen::Vector2d>& in_position, const Eigen::Rotation2Dd& in_orientation,
        foxglove::schemas::Pose& out) {
    out.position.emplace();
    to(in_position, *out.position);
    out.orientation.emplace();
    to(in_orientation, *out.orientation);
}

void to(const Eigen::Ref<const Eigen::Vector3d>& in_position, const Eigen::Quaterniond& in_orientation,
        foxglove::schemas::Pose& out) {
    out.position.emplace();
    to(in_position, *out.position);
    out.orientation.emplace();
    to(in_orientation, *out.orientation);
}

void to(const Eigen::Quaterniond& in, foxglove::schemas::Quaternion& out) {
    out.x = in.x();
    out.y = in.y();
    out.z = in.z();
    out.w = in.w();
}

void to(const Eigen::AngleAxisd& in, foxglove::schemas::Quaternion& out) {
    to(Eigen::Quaterniond{in}, out);
}

void to(const Eigen::Rotation2Dd& in, foxglove::schemas::Quaternion& out) {
    to(Eigen::AngleAxisd{in.angle(), Eigen::Vector3d::UnitZ()}, out);
}
}
