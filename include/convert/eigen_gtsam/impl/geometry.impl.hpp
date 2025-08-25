#ifndef CONVERT_EIGEN_GTSAM_IMPL_GEOMETRY_IMPL_HPP
#define CONVERT_EIGEN_GTSAM_IMPL_GEOMETRY_IMPL_HPP

#include "convert/eigen/geometry.hpp"
#include "convert/eigen_gtsam/impl/geometry.hpp"
#include "convert/impl/convert.hpp"

namespace convert {

CONVERT_INLINE void to(const gtsam::Pose3& p, Eigen::Isometry3d& i) {
    i = p.matrix();
}

CONVERT_INLINE void to(const gtsam::Rot3& r, Eigen::Quaterniond& q) {
    q = r.matrix();
}

CONVERT_INLINE void to(const gtsam::Rot3& r, Eigen::Ref<Eigen::Matrix3d> m) {
    m = r.matrix();
}

CONVERT_INLINE void to(const Eigen::Isometry3d& i, gtsam::Pose3& p) {
    p = gtsam::Pose3(i.matrix());
}

CONVERT_INLINE void to(const Eigen::Quaterniond& q, gtsam::Rot3& r) {
    r = gtsam::Rot3(q);
}

CONVERT_INLINE void to(const Eigen::Ref<const Eigen::Matrix3d>& m, gtsam::Rot3& r) {
    r = gtsam::Rot3(m);
}

}

#endif
