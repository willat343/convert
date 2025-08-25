#include "convert/eigen/geometry.hpp"

namespace convert {

template void to<double>(const Eigen::Vector3d&, Eigen::AngleAxisd&);
template void to<double>(const Eigen::AngleAxisd&, Eigen::Vector3d&);
template void to<double>(const Eigen::Translation2d&, const Eigen::Rotation2Dd&, Eigen::Isometry2d&);
template void to<double>(const Eigen::Vector2d&, const Eigen::Rotation2Dd&, Eigen::Isometry2d&);
template void to<double>(const Eigen::Translation3d&, const Eigen::Quaterniond&, Eigen::Isometry3d&);
template void to<double>(const Eigen::Vector3d&, const Eigen::Quaterniond&, Eigen::Isometry3d&);
template void to<double>(const Eigen::Translation2d&, const Eigen::Matrix2d&, Eigen::Isometry2d&);
template void to<double>(const Eigen::Vector2d&, const Eigen::Matrix2d&, Eigen::Isometry2d&);
template void to<double>(const Eigen::Translation3d&, const Eigen::Matrix3d&, Eigen::Isometry3d&);
template void to<double>(const Eigen::Vector3d&, const Eigen::Matrix3d&, Eigen::Isometry3d&);

}
