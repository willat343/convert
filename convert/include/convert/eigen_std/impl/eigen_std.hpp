#ifndef CONVERT_EIGEN_STD_IMPL_EIGEN_STD_HPP
#define CONVERT_EIGEN_STD_IMPL_EIGEN_STD_HPP

#include "convert/eigen_std/eigen_std.hpp"

namespace convert {

template<typename Scalar>
void to(const std::vector<Scalar>& in, Eigen::Matrix<Scalar, Eigen::Dynamic, 1>& out) {
    const std::size_t size = in.size();
    out.resize(static_cast<Eigen::Index>(size));
    for (std::size_t i = 0; i < size; ++i) {
        out[i] = in[i];
    }
}

template<typename Scalar>
void to(const Eigen::Matrix<Scalar, Eigen::Dynamic, 1>& in, std::vector<Scalar>& out) {
    const Eigen::Index size = in.size();
    out.resize(static_cast<std::size_t>(size));
    for (Eigen::Index i = 0; i < size; ++i) {
        out[i] = in[i];
    }
}

}

#endif
