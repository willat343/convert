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

template<typename Scalar>
inline void to(const Eigen::Translation<Scalar, 2>& t, const Eigen::Rotation2D<Scalar>& q,
        Eigen::Transform<Scalar, 2, Eigen::Isometry>& T) {
    T = t * q;
}

template<typename Scalar>
inline void to(const Eigen::Matrix<Scalar, 2, 1>& t, const Eigen::Rotation2D<Scalar>& q,
        Eigen::Transform<Scalar, 2, Eigen::Isometry>& T) {
    to(Eigen::Translation<Scalar, 2>{t}, q, T);
}

template<typename Scalar>
inline void to(const Eigen::Translation<Scalar, 3>& t, const Eigen::Quaternion<Scalar>& q,
        Eigen::Transform<Scalar, 3, Eigen::Isometry>& T) {
    T = t * q;
}

template<typename Scalar>
inline void to(const Eigen::Matrix<Scalar, 3, 1>& t, const Eigen::Quaternion<Scalar>& q,
        Eigen::Transform<Scalar, 3, Eigen::Isometry>& T) {
    to(Eigen::Translation<Scalar, 3>{t}, q, T);
}

template<typename Scalar>
void to(const Eigen::Translation<Scalar, 2>& t, const Eigen::Matrix<Scalar, 2, 2>& R,
        Eigen::Transform<Scalar, 2, Eigen::Isometry>& T) {
    to(t, Eigen::Rotation2D<Scalar>{R}, T);
}

template<typename Scalar>
inline void to(const Eigen::Matrix<Scalar, 2, 1>& t, const Eigen::Matrix<Scalar, 2, 2>& R,
        Eigen::Transform<Scalar, 2, Eigen::Isometry>& T) {
    to(Eigen::Translation<Scalar, 2>{t}, Eigen::Rotation2D<Scalar>{R}, T);
}

template<typename Scalar>
void to(const Eigen::Translation<Scalar, 3>& t, const Eigen::Matrix<Scalar, 3, 3>& R,
        Eigen::Transform<Scalar, 3, Eigen::Isometry>& T) {
    to(t, Eigen::Quaternion<Scalar>{R}, T);
}

template<typename Scalar>
inline void to(const Eigen::Matrix<Scalar, 3, 1>& t, const Eigen::Matrix<Scalar, 3, 3>& R,
        Eigen::Transform<Scalar, 3, Eigen::Isometry>& T) {
    to(Eigen::Translation<Scalar, 3>{t}, Eigen::Quaternion<Scalar>{R}, T);
}

}

#if !CONVERT_HEADER_ONLY
namespace convert {

extern template void to<double>(const Eigen::Vector3d&, Eigen::AngleAxisd&);
extern template void to<double>(const Eigen::AngleAxisd&, Eigen::Vector3d&);
extern template void to<double>(const Eigen::Translation2d&, const Eigen::Rotation2Dd&, Eigen::Isometry2d&);
extern template void to<double>(const Eigen::Vector2d&, const Eigen::Rotation2Dd&, Eigen::Isometry2d&);
extern template void to<double>(const Eigen::Translation3d&, const Eigen::Quaterniond&, Eigen::Isometry3d&);
extern template void to<double>(const Eigen::Vector3d&, const Eigen::Quaterniond&, Eigen::Isometry3d&);
extern template void to<double>(const Eigen::Translation2d&, const Eigen::Matrix2d&, Eigen::Isometry2d&);
extern template void to<double>(const Eigen::Vector2d&, const Eigen::Matrix2d&, Eigen::Isometry2d&);
extern template void to<double>(const Eigen::Translation3d&, const Eigen::Matrix3d&, Eigen::Isometry3d&);
extern template void to<double>(const Eigen::Vector3d&, const Eigen::Matrix3d&, Eigen::Isometry3d&);

}
#endif

#endif
