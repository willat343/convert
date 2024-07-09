#ifndef CONVERT_IMPL_EIGEN_ROS_HPP
#define CONVERT_IMPL_EIGEN_ROS_HPP

#include "convert/eigen_ros/eigen_ros.hpp"

namespace convert {

template<typename ArrayScalar, int Rows, int Cols, typename MatrixScalar = ArrayScalar>
void to(const boost::array<ArrayScalar, Rows * Cols>& msg, Eigen::Ref<Eigen::Matrix<MatrixScalar, Rows, Cols>> m) {
    for (std::size_t r = 0; r < Rows; ++r) {
        for (std::size_t c = 0; c < Cols; ++c) {
            m(r, c) = msg[Cols * r + c];
        }
    }
}

template<typename MatrixScalar, int Rows, int Cols, typename ArrayScalar = MatrixScalar>
void to(const Eigen::Ref<const Eigen::Matrix<MatrixScalar, Rows, Cols>> m,
        boost::array<ArrayScalar, Rows * Cols>& msg) {
    for (std::size_t r = 0; r < Rows; ++r) {
        for (std::size_t c = 0; c < Cols; ++c) {
            msg[Cols * r + c] = m(r, c);
        }
    }
}

template<typename VectorScalar, typename MatrixScalar = VectorScalar>
void to(const std::vector<VectorScalar>& msg,
        Eigen::Ref<Eigen::Matrix<MatrixScalar, Eigen::Dynamic, Eigen::Dynamic>> m) {
    const std::size_t Rows = m.rows();
    const std::size_t Cols = m.cols();
    if (msg.size() != Rows * Cols) {
        throw std::runtime_error("Failed to convert from ros vector to matrix. Vector size " +
                                 std::to_string(msg.size()) + " != " + std::to_string(Rows) + "*" +
                                 std::to_string(Cols) + " (Rows*Cols). Were the matrix dimensions set correctly?");
    }
    for (std::size_t r = 0; r < Rows; ++r) {
        for (std::size_t c = 0; c < Cols; ++c) {
            m(r, c) = msg[Cols * r + c];
        }
    }
}

template<typename MatrixScalar, typename VectorScalar = MatrixScalar>
void to(const Eigen::Ref<const Eigen::Matrix<MatrixScalar, Eigen::Dynamic, Eigen::Dynamic>> m,
        std::vector<VectorScalar>& msg) {
    const std::size_t Rows = m.rows();
    const std::size_t Cols = m.cols();
    msg.resize(Rows * Cols);
    for (std::size_t r = 0; r < Rows; ++r) {
        for (std::size_t c = 0; c < Cols; ++c) {
            msg[Cols * r + c] = m(r, c);
        }
    }
}

}

#endif
