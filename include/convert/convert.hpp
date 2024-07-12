#ifndef CONVERT_CONVERT_HPP
#define CONVERT_CONVERT_HPP

#if defined(CONVERT_EIGEN)
#include "convert/eigen/eigen.hpp"
#endif
#if defined(CONVERT_EIGEN) && defined(CONVERT_GTSAM)
#include "convert/eigen_gtsam/eigen_gtsam.hpp"
#endif
#if defined(CONVERT_EIGEN) && defined(CONVERT_ROS)
#include "convert/eigen_ros/eigen_ros.hpp"
#endif
#if defined(CONVERT_EIGEN) && defined(CONVERT_MATLAB)
#include "convert/eigen_matlab/eigen_matlab.hpp"
#endif
#if defined(CONVERT_GTSAM) && defined(CONVERT_ROS)
#include "convert/gtsam_ros/gtsam_ros.hpp"
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
#if defined(CONVERT_ROS) && defined(CONVERT_SENSORBOX)
#include "convert/sensorbox_ros/sensorbox_ros.hpp"
#endif

#include "convert/convert_helpers.hpp"

#endif
