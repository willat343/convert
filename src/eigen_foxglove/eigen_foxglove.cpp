#include "convert/eigen_foxglove/impl/eigen_foxglove.impl.hpp"

namespace convert {

template void to<Eigen::Vector3d>(const Eigen::MatrixBase<Eigen::Vector3d>&, foxglove::schemas::Vector3&);
template void to<2>(const Eigen::Isometry2d&, foxglove::schemas::Pose&);
template void to<3>(const Eigen::Isometry3d&, foxglove::schemas::Pose&);
template void to<2>(const std::string& in_parent_frame, const std::string& in_child_frame, const Eigen::Isometry2d&,
        foxglove::schemas::FrameTransform&);
template void to<3>(const std::string& in_parent_frame, const std::string& in_child_frame, const Eigen::Isometry3d&,
        foxglove::schemas::FrameTransform&);

}
