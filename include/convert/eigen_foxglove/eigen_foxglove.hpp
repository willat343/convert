#ifndef CONVERT_EIGEN_FOXGLOVE_EIGEN_FOXGLOVE_HPP
#define CONVERT_EIGEN_FOXGLOVE_EIGEN_FOXGLOVE_HPP

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <foxglove/schemas.hpp>

namespace convert {

void to(const Eigen::Ref<const Eigen::Vector3d>& in, foxglove::schemas::Vector3& out);

void to(const Eigen::Ref<const Eigen::Vector2d>& in, foxglove::schemas::Vector2& out);

void to(const Eigen::Ref<const Eigen::Vector2d>& in, foxglove::schemas::Vector3& out);

template<typename Derived>
void to(const Eigen::MatrixBase<Derived>& in, foxglove::schemas::Vector3& out);

void to(const Eigen::Ref<const Eigen::Vector2d>& in_position, const Eigen::Rotation2Dd& in_orientation,
        foxglove::schemas::Pose& out);

void to(const Eigen::Ref<const Eigen::Vector3d>& in_position, const Eigen::Quaterniond& in_orientation,
        foxglove::schemas::Pose& out);

void to(const Eigen::Quaterniond& in, foxglove::schemas::Quaternion& out);

void to(const Eigen::AngleAxisd& in, foxglove::schemas::Quaternion& out);

void to(const Eigen::Rotation2Dd& in, foxglove::schemas::Quaternion& out);

template<int D>
    requires(D == 2 || D == 3)
void to(const Eigen::Transform<double, D, Eigen::Isometry>& in, foxglove::schemas::Pose& out);

template<int D>
    requires(D == 2 || D == 3)
void to(const std::string& in_parent_frame, const std::string& in_child_frame,
        const Eigen::Transform<double, D, Eigen::Isometry>& in_transform, foxglove::schemas::FrameTransform& out);

}

#include "convert/eigen_foxglove/impl/eigen_foxglove.hpp"

#endif
