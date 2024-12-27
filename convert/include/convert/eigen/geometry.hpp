#ifndef CONVERT_EIGEN_GEOMETRY_HPP
#define CONVERT_EIGEN_GEOMETRY_HPP

#include <Eigen/Core>
#include <Eigen/Geometry>

namespace convert {

/**
 * @brief Convert a vector representing an angle-axis rotation in form \f$\mathbf{r} = \Vert \mathbf{r} \Vert
 * \mathbf{\hat{r}}\f$ to angle-axis object. If the angle \f$\Vert \mathbf{r} \Vert == 0\f$, then the unit X axis is
 * used.
 *
 * @tparam Scalar
 * @param v
 * @param aa
 */
template<typename Scalar>
void to(const Eigen::Matrix<Scalar, 3, 1>& v, Eigen::AngleAxis<Scalar>& aa);

/**
 * @brief Convert an angle-axis object to a vector \f$\mathbf{r}\f$ by multiplying the angle \f$\Vert \mathbf{r}
 * \Vert\f$ by the rotation axis \f$\mathbf{\hat{r}}\f$.
 *
 * @tparam Scalar
 * @param aa
 * @param v
 */
template<typename Scalar>
void to(const Eigen::AngleAxis<Scalar>& aa, Eigen::Matrix<Scalar, 3, 1>& v);

/**
 * @brief Convert translation and quaternion to transform.
 *
 * @tparam Scalar
 * @tparam D
 * @param t
 * @param q
 * @param T
 */
template<typename Scalar, int D>
void to(const Eigen::Translation<Scalar, D>& t, const Eigen::Quaternion<Scalar>& q,
        Eigen::Transform<Scalar, D, Eigen::Isometry>& T);

/**
 * @brief Convert translation vector and quaternion to transform.
 *
 * @tparam Scalar
 * @tparam D
 * @param t
 * @param q
 * @param T
 */
template<typename Scalar, int D>
void to(const Eigen::Matrix<Scalar, D, 1>& t, const Eigen::Quaternion<Scalar>& q,
        Eigen::Transform<Scalar, D, Eigen::Isometry>& T);

/**
 * @brief Convert translation and rotation matrix to transform.
 *
 * @tparam Scalar
 * @tparam D
 * @param t
 * @param R
 * @param T
 */
template<typename Scalar, int D>
void to(const Eigen::Translation<Scalar, D>& t, const Eigen::Matrix<Scalar, D, D>& R,
        Eigen::Transform<Scalar, D, Eigen::Isometry>& T);

/**
 * @brief Convert translation vector and rotation matrix to transform.
 *
 * @tparam Scalar
 * @tparam D
 * @param t
 * @param R
 * @param T
 */
template<typename Scalar, int D>
void to(const Eigen::Matrix<Scalar, D, 1>& t, const Eigen::Matrix<Scalar, D, D>& R,
        Eigen::Transform<Scalar, D, Eigen::Isometry>& T);

}

#include "convert/eigen/impl/geometry.hpp"

#endif
