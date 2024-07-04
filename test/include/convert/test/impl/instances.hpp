#ifndef CONVERT_IMPL_TEST_INSTANCES_HPP
#define CONVERT_IMPL_TEST_INSTANCES_HPP

#ifdef CONVERT_EIGEN
#include <Eigen/Core>
#include <Eigen/Geometry>
#endif

#ifdef CONVERT_MANIF
#include <manif/Rn.h>
#include <manif/SO3.h>
#include <manif/manif.h>
#endif

#ifdef CONVERT_ROS
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/Vector3.h>
#include <ros/ros.h>
#endif

#include <cstdlib>

#include "convert/test/instances.hpp"

namespace convert::test {

template<typename T, int N>
std::array<T, N> test_instances(const unsigned int seed) {
    srand(seed);
    std::array<T, N> instances;
    for (std::size_t i = 0; i < N; ++i) {
        instances[i] = random_instance<T>();
    }
    return instances;
}

template<typename T>
std::vector<T> test_instances(const std::size_t count, const unsigned int seed) {
    srand(seed);
    std::vector<T> instances(count);
    for (std::size_t i = 0; i < count; ++i) {
        instances[i] = random_instance<T>();
    }
    return instances;
}

template<>
inline float random_instance<float>() {
    return 2.f * static_cast<float>(rand()) / static_cast<float>(RAND_MAX) - 1.f;
}

template<>
inline double random_instance<double>() {
    return 2.0 * static_cast<double>(rand()) / static_cast<double>(RAND_MAX) - 1.0;
}

#ifdef CONVERT_EIGEN
template<>
inline Eigen::Vector3d random_instance<Eigen::Vector3d>() {
    return Eigen::Vector3d::Random();
}

template<>
inline Eigen::Quaterniond random_instance<Eigen::Quaterniond>() {
    return Eigen::Quaterniond::UnitRandom();
}
#endif

#ifdef CONVERT_MANIF
template<>
inline manif::SO3d random_instance<manif::SO3d>() {
    return manif::SO3d::Random();
}

template<>
inline manif::R3d random_instance<manif::R3d>() {
    return manif::R3d::Random();
}
#endif

#ifdef CONVERT_ROS
template<>
inline geometry_msgs::Point random_instance<geometry_msgs::Point>() {
    geometry_msgs::Point instance;
    instance.x = random_instance<double>();
    instance.y = random_instance<double>();
    instance.z = random_instance<double>();
    return instance;
}

template<>
inline geometry_msgs::Quaternion random_instance<geometry_msgs::Quaternion>() {
    geometry_msgs::Quaternion instance;
    const double w = random_instance<double>();
    const double x = random_instance<double>();
    const double y = random_instance<double>();
    const double z = random_instance<double>();
    const double norm = std::sqrt(w * w + x * x + y * y + z * z);
    instance.w = w / norm;
    instance.x = x / norm;
    instance.y = y / norm;
    instance.z = z / norm;
    return instance;
}

template<>
inline geometry_msgs::Vector3 random_instance<geometry_msgs::Vector3>() {
    geometry_msgs::Vector3 instance;
    instance.x = random_instance<double>();
    instance.y = random_instance<double>();
    instance.z = random_instance<double>();
    return instance;
}
#endif

}

#endif
