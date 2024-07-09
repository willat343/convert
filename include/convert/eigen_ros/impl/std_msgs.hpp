#ifndef CONVERT_EIGEN_ROS_IMPL_STD_MSGS_HPP
#define CONVERT_EIGEN_ROS_IMPL_STD_MSGS_HPP

#include "convert/eigen_ros/std_msgs.hpp"

namespace convert {

template<typename Derived>
void to(const Eigen::MatrixBase<Derived>& matrix, std_msgs::Float64MultiArray& msg) {
    const Eigen::Index size = matrix.size();
    const Eigen::Index rows = matrix.rows();
    const Eigen::Index cols = matrix.cols();
    msg.data.resize(matrix.size());
    for (Eigen::Index r = 0; r < rows; ++r) {
        for (Eigen::Index c = 0; c < cols; ++c) {
            msg.data[r * cols + c] = matrix(r, c);
        }
    }
    msg.layout.data_offset = 0;
    std_msgs::MultiArrayDimension row_dim;
    row_dim.label = "rows";
    row_dim.size = rows;
    row_dim.stride = size;
    msg.layout.dim.push_back(row_dim);
    std_msgs::MultiArrayDimension col_dim;
    col_dim.label = "cols";
    col_dim.size = cols;
    col_dim.stride = cols;
    msg.layout.dim.push_back(col_dim);
}

template<typename Derived>
void to(const std_msgs::Float64MultiArray& msg, Eigen::MatrixBase<Derived>& matrix) {
    if (msg.layout.dim.size() != 2 || static_cast<Eigen::Index>(msg.layout.dim[0].size) != matrix.rows() ||
            static_cast<Eigen::Index>(msg.layout.dim[1].size) != matrix.cols()) {
        throw std::runtime_error("Float64MultiArray msg dimensions did not match that of the matrix (" +
                                 std::to_string(matrix.rows()) + ", " + std::to_string(matrix.cols()));
    }
    for (std::uint32_t r = 0; r < msg.layout.dim[0].size; ++r) {
        for (std::uint32_t c = 0; c < msg.layout.dim[1].size; ++c) {
            matrix(r, c) = msg.data[msg.layout.data_offset + msg.layout.dim[1].stride * r + c];
        }
    }
}

}

#endif
