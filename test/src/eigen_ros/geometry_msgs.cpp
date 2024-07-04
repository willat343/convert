#include "convert/eigen_ros/geometry_msgs.hpp"

#include <gtest/gtest.h>

#include "convert/test/geometry_msgs.hpp"
#include "convert/test/helpers.hpp"
#include "convert/test/instances.hpp"

TEST(quaterniond_quaternion, to_from) {
    convert::test::test_to_from_eq<Eigen::Quaterniond>(geometry_msgs::Quaternion());
    auto instances = convert::test::test_instances<geometry_msgs::Quaternion, 100>();
    for (unsigned int i = 0; i < instances.size(); ++i) {
        convert::test::check_approx(instances[i],
                convert::to<geometry_msgs::Quaternion>(convert::to<Eigen::Quaterniond>(instances[i])));
    }
}

TEST(vector3d_point, to_from) {
    convert::test::test_to_from_eq<Eigen::Vector3d>(geometry_msgs::Point());
    auto instances = convert::test::test_instances<geometry_msgs::Point, 100>();
    for (unsigned int i = 0; i < instances.size(); ++i) {
        convert::test::test_to_from_eq<Eigen::Vector3d>(instances[i]);
    }
}

TEST(vector3d_vector3, to_from) {
    convert::test::test_to_from_eq<Eigen::Vector3d>(geometry_msgs::Vector3());
    auto instances = convert::test::test_instances<geometry_msgs::Vector3, 100>();
    for (unsigned int i = 0; i < instances.size(); ++i) {
        convert::test::test_to_from_eq<Eigen::Vector3d>(instances[i]);
    }
}

TEST(point_vector3d, to_from) {
    convert::test::test_to_from_eq<geometry_msgs::Point, Eigen::Vector3d>(Eigen::Vector3d::Zero());
    convert::test::test_to_from_eq<geometry_msgs::Point, Eigen::Vector3d>(Eigen::Vector3d::Ones());
    auto instances = convert::test::test_instances<Eigen::Vector3d, 100>();
    for (unsigned int i = 0; i < instances.size(); ++i) {
        convert::test::test_to_from_eq<geometry_msgs::Point>(instances[i]);
    }
}

TEST(quaternion_quaterniond, to_from) {
    // Note that operator== not defined for Eigen::Quaternion<Scalar> until Eigen 3.4
    convert::test::test_to_from_is_approx<geometry_msgs::Quaternion>(Eigen::Quaterniond::Identity());
    auto instances = convert::test::test_instances<Eigen::Quaterniond, 100>();
    for (unsigned int i = 0; i < instances.size(); ++i) {
        convert::test::test_to_from_is_approx<geometry_msgs::Quaternion>(instances[i]);
    }
}

TEST(vector3_vector3d, to_from) {
    convert::test::test_to_from_eq<geometry_msgs::Vector3, Eigen::Vector3d>(Eigen::Vector3d::Zero());
    convert::test::test_to_from_eq<geometry_msgs::Vector3, Eigen::Vector3d>(Eigen::Vector3d::Ones());
    auto instances = convert::test::test_instances<Eigen::Vector3d, 100>();
    for (unsigned int i = 0; i < instances.size(); ++i) {
        convert::test::test_to_from_eq<geometry_msgs::Vector3>(instances[i]);
    }
}
