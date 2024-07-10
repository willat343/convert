#ifndef CONVERT_EIGEN_IMPL_GEOMETRY_HPP
#define CONVERT_EIGEN_IMPL_GEOMETRY_HPP

#include "convert/eigen/geometry.hpp"

namespace convert {

template<typename Scalar>
inline void to(const Eigen::Matrix<Scalar, 3, 1>& v, Eigen::AngleAxis<Scalar>& aa) {
    const Scalar angle = v.norm();
    aa.angle() = angle;
    aa.axis() = (angle == static_cast<Scalar>(0) ? Eigen::Matrix<Scalar, 3, 1>::UnitX() : (v / angle).eval());
}

template<typename Scalar>
inline void to(const Eigen::AngleAxis<Scalar>& aa, Eigen::Matrix<Scalar, 3, 1>& v) {
    v = aa.angle() * aa.axis();
}

}

#endif
