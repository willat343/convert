#ifndef CONVERT_EIGEN_MATLAB_IMPL_EIGEN_MATLAB_HPP
#define CONVERT_EIGEN_MATLAB_IMPL_EIGEN_MATLAB_HPP

#include "convert/eigen_matlab/eigen_matlab.hpp"

namespace convert {

template<typename MatrixType>
std::vector<MatrixType> to_matrices(const matlab::data::CellArray& array) {
    const matlab::data::ArrayDimensions dimensions = array.getDimensions();
    if (dimensions.size() > 1 && dimensions[1] > 1) {
        throw std::runtime_error("Failed to convert MATLAB cell array to Eigen matrices. Invalid cell dimensions.");
    }
    std::vector<MatrixType> matrices;
    const int size = dimensions[0];
    for (int i = 0; i < size; ++i) {
        matrices.emplace_back(to_matrix<MatrixType>(array[i]));
    }
    return matrices;
}

template<typename MatrixType>
inline MatrixType to_matrix(const matlab::data::Array& array) {
    return to_matrix<MatrixType>(matlab::data::TypedArray<typename MatrixType::Scalar>(array));
}

template<typename MatrixType>
MatrixType to_matrix(const matlab::data::TypedArray<typename MatrixType::Scalar>& array) {
    const int rows = array.getDimensions()[0];
    const int cols = array.getDimensions()[1];
    assert(MatrixType::RowsAtCompileTime == Eigen::Dynamic || MatrixType::RowsAtCompileTime == rows);
    assert(MatrixType::ColsAtCompileTime == Eigen::Dynamic || MatrixType::ColsAtCompileTime == cols);
    if ((MatrixType::RowsAtCompileTime != Eigen::Dynamic && MatrixType::RowsAtCompileTime != rows) ||
            (MatrixType::ColsAtCompileTime != Eigen::Dynamic && MatrixType::ColsAtCompileTime != cols)) {
        throw std::runtime_error("Failed to convert MATLAB array to Eigen matrix. Invalid row or column sizes.");
    }
    MatrixType x(rows, cols);
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            x(r, c) = array[r][c];
        }
    }
    return x;
}

template<typename Derived>
matlab::data::TypedArray<typename Derived::Scalar> to_array(const Eigen::DenseBase<Derived>& matrix,
        matlab::data::ArrayFactory& factory) {
    const unsigned int rows = static_cast<unsigned int>(matrix.rows());
    const unsigned int cols = static_cast<unsigned int>(matrix.cols());
    matlab::data::TypedArray<typename Derived::Scalar> array =
            factory.createArray<typename Derived::Scalar>({rows, cols});
    for (unsigned int r = 0; r < rows; ++r) {
        for (unsigned int c = 0; c < cols; ++c) {
            array[r][c] = matrix(r, c);
        }
    }
    return array;
}

}

#endif