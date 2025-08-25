#ifndef CONVERT_EIGEN_GTSAM_IMPL_NAVIGATION_IMPL_HPP
#define CONVERT_EIGEN_GTSAM_IMPL_NAVIGATION_IMPL_HPP

#include "convert/eigen_gtsam/geometry.hpp"
#include "convert/eigen_gtsam/impl/navigation.hpp"
#include "convert/impl/convert.hpp"

namespace convert {

CONVERT_INLINE void to(const gtsam::NavState& navstate, Eigen::Isometry3d& pose, Eigen::Vector3d& velocity) {
    to(navstate.pose(), pose);
    velocity = navstate.velocity();
}

CONVERT_INLINE void to(const Eigen::Isometry3d& pose, const Eigen::Vector3d& velocity, gtsam::NavState& navstate) {
    gtsam::Pose3 pose_gtsam;
    to(pose, pose_gtsam);
    navstate = gtsam::NavState{pose_gtsam, velocity};
}

}

#endif
