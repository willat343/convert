#ifndef CONVERT_EIGEN_STD_EIGEN_STD_HPP
#define CONVERT_EIGEN_STD_EIGEN_STD_HPP

#include <Eigen/Core>
#include <vector>

namespace convert {

template<typename Scalar>
void to(const std::vector<Scalar>& in, Eigen::Matrix<Scalar, Eigen::Dynamic, 1>& out);

template<typename Scalar>
void to(const Eigen::Matrix<Scalar, Eigen::Dynamic, 1>& in, std::vector<Scalar>& out);

}

#include "convert/eigen_std/impl/eigen_std.hpp"

#endif
