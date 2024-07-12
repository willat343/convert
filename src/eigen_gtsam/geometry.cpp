#include "convert/eigen_gtsam/geometry.hpp"
#include "convert/eigen/geometry.hpp"

namespace convert {

void to(const gtsam::Pose3& p, Eigen::Isometry3d& i) {
    i = p.matrix();
}

void to(const gtsam::Rot3& r, Eigen::Quaterniond& q) {
    q = r.matrix();
}

void to(const gtsam::Rot3& r, Eigen::Ref<Eigen::Matrix3d> m) {
    m = r.matrix();
}

void to(const Eigen::Isometry3d& i, gtsam::Pose3& p) {
    p = gtsam::Pose3(i.matrix());
}

void to(const Eigen::Quaterniond& q, gtsam::Rot3& r) {
    r = gtsam::Rot3(q);
}

void to(const Eigen::Ref<const Eigen::Matrix3d>& m, gtsam::Rot3& r) {
    r = gtsam::Rot3(m);
}

}
