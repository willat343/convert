#ifndef CONVERT_EIGEN_GTSAM_NAVIGATION_HPP
#define CONVERT_EIGEN_GTSAM_NAVIGATION_HPP

#include <gtsam/navigation/NavState.h>
#include <Eigen/Core>
#include <Eigen/Geometry>

namespace convert {

void to(const gtsam::NavState& navstate, Eigen::Isometry3d& pose, Eigen::Vector3d& velocity);

void to(const Eigen::Isometry3d& pose, const Eigen::Vector3d& velocity, gtsam::NavState& navstate);

}

#endif
