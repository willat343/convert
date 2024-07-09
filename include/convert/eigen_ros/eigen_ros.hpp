#ifndef CONVERT_EIGEN_ROS_HPP
#define CONVERT_EIGEN_ROS_HPP

#include <ros/ros.h>

#include <Eigen/Core>
#include <vector>

#include "convert/eigen_ros/geometry_msgs.hpp"
#include "convert/eigen_ros/std_msgs.hpp"

namespace convert {

/**
 * @brief Convert a boost::array to an Eigen::Matrix.
 *
 * @tparam ArrayScalar
 * @tparam Rows
 * @tparam Cols
 * @tparam MatrixScalar
 * @param msg
 * @param m
 */
template<typename ArrayScalar, int Rows, int Cols, typename MatrixScalar = ArrayScalar>
void to(const boost::array<ArrayScalar, Rows * Cols>& msg, Eigen::Ref<Eigen::Matrix<MatrixScalar, Rows, Cols>> m);

/**
 * @brief Convert an Eigen::Matrix to a boost::array.
 *
 * @tparam MatrixScalar
 * @tparam Rows
 * @tparam Cols
 * @tparam ArrayScalar
 * @param m
 * @param msg
 */
template<typename MatrixScalar, int Rows, int Cols, typename ArrayScalar = MatrixScalar>
void to(const Eigen::Ref<const Eigen::Matrix<MatrixScalar, Rows, Cols>> m, boost::array<ArrayScalar, Rows * Cols>& msg);

/**
 * @brief Convert a std::vector of scalars to an Eigen::Matrix.
 *
 * @tparam VectorScalar
 * @tparam MatrixScalar
 * @param msg
 * @param m
 */
template<typename VectorScalar, typename MatrixScalar = VectorScalar>
void to(const std::vector<VectorScalar>& msg,
        Eigen::Ref<Eigen::Matrix<MatrixScalar, Eigen::Dynamic, Eigen::Dynamic>> m);

/**
 * @brief Convert an Eigen::Matrix to a std::vector of scalars.
 *
 * @tparam MatrixScalar
 * @tparam VectorScalar
 * @param m
 * @param msg
 */
template<typename MatrixScalar, typename VectorScalar = MatrixScalar>
void to(const Eigen::Ref<const Eigen::Matrix<MatrixScalar, Eigen::Dynamic, Eigen::Dynamic>> m,
        std::vector<VectorScalar>& msg);

}

#include "convert/eigen_ros/impl/eigen_ros.hpp"

#endif
