#ifndef CONVERT_EIGEN_FOXGLOVE_IMPL_EIGEN_FOXGLOVE_HPP
#define CONVERT_EIGEN_FOXGLOVE_IMPL_EIGEN_FOXGLOVE_HPP

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <foxglove/schemas.hpp>

#include "convert/eigen_foxglove/eigen_foxglove.hpp"

namespace convert {

template<typename Derived>
void to(const Eigen::MatrixBase<Derived>& in, foxglove::schemas::Vector3& out) {
    static_assert(Derived::ColsAtCompileTime == 1, "Input must be a column vector");
    static_assert(Derived::RowsAtCompileTime == 2 || Derived::RowsAtCompileTime == 3,
            "Only 2D or 3D vectors supported");
    if constexpr (Derived::RowsAtCompileTime == 2) {
        out.x = in[0];
        out.y = in[1];
        out.z = 0.0;
    } else {
        out.x = in[0];
        out.y = in[1];
        out.z = in[2];
    }
}

template<int D>
    requires(D == 2 || D == 3)
void to(const Eigen::Transform<double, D, Eigen::Isometry>& in, foxglove::schemas::Pose& out) {
    out.position.emplace();
    to(in.translation(), *out.position);
    out.orientation.emplace();
    if constexpr (D == 2) {
        to(Eigen::Rotation2Dd{in.rotation()}, *out.orientation);
    } else {
        to(Eigen::Quaterniond{in.rotation()}, *out.orientation);
    }
}

template<int D>
    requires(D == 2 || D == 3)
void to(const std::string& in_parent_frame, const std::string& in_child_frame,
        const Eigen::Transform<double, D, Eigen::Isometry>& in_transform, foxglove::schemas::FrameTransform& out) {
    out.timestamp = std::nullopt;
    out.parent_frame_id = in_parent_frame;
    out.child_frame_id = in_child_frame;
    out.translation.emplace();
    to(in_transform.translation(), *out.translation);
    out.rotation.emplace();
    if constexpr (D == 2) {
        to(Eigen::Rotation2Dd{in_transform.rotation()}, *out.rotation);
    } else {
        to(Eigen::Quaterniond{in_transform.rotation()}, *out.rotation);
    }
}

}

#endif
