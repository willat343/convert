#ifndef CONVERT_CONVERT_HPP
#define CONVERT_CONVERT_HPP

#if defined(CONVERT_EIGEN) && defined(CONVERT_ROS)
#include "convert/eigen_ros/eigen_ros.hpp"
#endif
#if defined(CONVERT_EIGEN) && defined(CONVERT_MATLAB)
#include "convert/eigen_matlab/eigen_matlab.hpp"
#endif
#if defined(CONVERT_MANIF) && defined(CONVERT_ROS)
#include "convert/manif_ros/manif_ros.hpp"
#endif
#if defined(CONVERT_MATLAB)
#include "convert/matlab_std/matlab_std.hpp"
#endif
#if defined(CONVERT_ROS)
#include "convert/ros/ros.hpp"
#endif

#include "convert/convert_helpers.hpp"

#endif
