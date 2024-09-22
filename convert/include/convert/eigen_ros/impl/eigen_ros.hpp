#ifndef CONVERT_IMPL_EIGEN_ROS_HPP
#define CONVERT_IMPL_EIGEN_ROS_HPP

#include "convert/eigen_ros/eigen_ros.hpp"

namespace convert {

template<typename ArrayScalar, std::size_t Size, typename Derived>
void to(const boost::array<ArrayScalar, Size>& msg, Eigen::MatrixBase<Derived>& m) {
    static_assert(Derived::SizeAtCompileTime == Size, "conversion only supports fixed-size matrices of correct size");
    for (int r = 0; r < Derived::RowsAtCompileTime; ++r) {
        for (int c = 0; c < Derived::ColsAtCompileTime; ++c) {
            m(r, c) = msg[Derived::ColsAtCompileTime * r + c];
        }
    }
}

template<typename ArrayScalar, std::size_t Size, typename Derived>
void to(const Eigen::MatrixBase<Derived>& m, boost::array<ArrayScalar, Size>& msg) {
    static_assert(Derived::SizeAtCompileTime == Size, "conversion only supports fixed-size matrices of correct size");
    for (int r = 0; r < Derived::RowsAtCompileTime; ++r) {
        for (int c = 0; c < Derived::ColsAtCompileTime; ++c) {
            msg[Derived::ColsAtCompileTime * r + c] = m(r, c);
        }
    }
}

}

#endif
