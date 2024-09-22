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

template<typename Scalar, int D>
inline void to(const Eigen::Translation<Scalar, D>& t, const Eigen::Quaternion<Scalar>& q,
        Eigen::Transform<Scalar, D, Eigen::Isometry>& T) {
    T = t * q;
}

template<typename Scalar, int D>
inline void to(const Eigen::Matrix<Scalar, D, 1>& t, const Eigen::Quaternion<Scalar>& q,
        Eigen::Transform<Scalar, D, Eigen::Isometry>& T) {
    to(Eigen::Translation<Scalar, D>{t}, q, T);
}

template<typename Scalar, int D>
void to(const Eigen::Translation<Scalar, D>& t, const Eigen::Matrix<Scalar, D, D>& R,
        Eigen::Transform<Scalar, D, Eigen::Isometry>& T) {
    to(t, Eigen::Quaternion<Scalar>{R}, T);
}

template<typename Scalar, int D>
inline void to(const Eigen::Matrix<Scalar, D, 1>& t, const Eigen::Matrix<Scalar, D, D>& R,
        Eigen::Transform<Scalar, D, Eigen::Isometry>& T) {
    to(Eigen::Translation<Scalar, D>{t}, Eigen::Quaternion<Scalar>{R}, T);
}

}

#endif
