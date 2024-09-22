#ifndef CONVERT_EIGEN_GTSAM_GEOMETRY_HPP
#define CONVERT_EIGEN_GTSAM_GEOMETRY_HPP

#include <gtsam/geometry/Pose3.h>
#include <Eigen/Core>
#include <Eigen/Geometry>

namespace convert {

void to(const gtsam::Pose3& p, Eigen::Isometry3d& i);

void to(const gtsam::Rot3& r, Eigen::Quaterniond& q);

void to(const gtsam::Rot3& r, Eigen::Ref<Eigen::Matrix3d> m);

void to(const Eigen::Isometry3d& i, gtsam::Pose3& p);

void to(const Eigen::Quaterniond& q, gtsam::Rot3& r);

void to(const Eigen::Ref<const Eigen::Matrix3d>& m, gtsam::Rot3& r);

}

#endif
