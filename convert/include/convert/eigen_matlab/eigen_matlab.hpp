#ifndef CONVERT_EIGEN_MATLAB_EIGEN_MATLAB_HPP
#define CONVERT_EIGEN_MATLAB_EIGEN_MATLAB_HPP

#include <Eigen/Core>
#include <mex.hpp>

namespace convert {

/**
 * @brief Convert matlab cell array to vector of eigen matrices. It is assumes that the cell array has one dimension and
 * that the internal arrays can be cast to a `matlab::data::TypedArray<typename MatrixType::Scalar>` and that the
 * dimensions of each of these arrays matches that of `MatrixType`.
 *
 * @tparam MatrixType
 * @param array
 * @return std::vector<MatrixType>
 */
template<typename MatrixType>
std::vector<MatrixType> to_matrices(const matlab::data::CellArray& array);

/**
 * @brief Convert matlab data array to eigen matrix. This is a shorthand for
 * `to(const matlab::data::TypedArray<typename MatrixType::Scalar>& array)` so it is assumed `array` can be cast to a
 * `matlab::data::TypedArray<typename MatrixType::Scalar>`.
 *
 * @tparam MatrixType
 * @param array
 * @return MatrixType
 */
template<typename MatrixType>
MatrixType to_matrix(const matlab::data::Array& array);

/**
 * @brief Convert matlab data array to eigen matrix. The dimensions of MatrixType must match those of the matlab array
 * (or be dynamic).
 *
 * @tparam MatrixType
 * @param array
 * @return MatrixType
 */
template<typename MatrixType>
MatrixType to_matrix(const matlab::data::TypedArray<typename MatrixType::Scalar>& array);

/**
 * @brief Convert Eigen matrix to matlab array.
 *
 * @tparam Derived
 * @param matrix
 * @param factory
 * @return matlab::data::TypedArray<typename Derived::Scalar>
 */
template<typename Derived>
matlab::data::TypedArray<typename Derived::Scalar> to_array(const Eigen::DenseBase<Derived>& matrix,
        matlab::data::ArrayFactory& factory);

}

#include "convert/eigen_matlab/impl/eigen_matlab.hpp"

#endif
