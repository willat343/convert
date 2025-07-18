#ifndef CONVERT_EIGEN_STD_EIGEN_STD_HPP
#define CONVERT_EIGEN_STD_EIGEN_STD_HPP

#include <Eigen/Core>
#include <vector>

namespace convert {

template<typename Scalar>
void to(const std::vector<Scalar>& in, Eigen::Matrix<Scalar, Eigen::Dynamic, 1>& out);

template<std::size_t N, typename Scalar>
void to(const std::array<Scalar, N>& in, Eigen::Matrix<Scalar, int(N), 1>& out);

template<typename Scalar>
void to(const Eigen::Matrix<Scalar, Eigen::Dynamic, 1>& in, std::vector<Scalar>& out);

template<std::size_t N, typename Scalar>
void to(const Eigen::Matrix<Scalar, int(N), 1>& in, std::array<Scalar, N>& out);

}

#include "convert/eigen_std/impl/eigen_std.hpp"

#endif
