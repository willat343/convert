#include "convert/eigen_gtsam/navigation.hpp"
#include "convert/eigen_gtsam/geometry.hpp"

namespace convert {

void to(const gtsam::NavState& navstate, Eigen::Isometry3d& pose, Eigen::Vector3d& velocity) {
    to(navstate.pose(), pose);
    velocity = navstate.velocity();
}

void to(const Eigen::Isometry3d& pose, const Eigen::Vector3d& velocity, gtsam::NavState& navstate) {
    gtsam::Pose3 pose_gtsam;
    to(pose, pose_gtsam);
    navstate = gtsam::NavState{pose_gtsam, velocity};
}

}
