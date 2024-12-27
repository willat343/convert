#include "convert/manif_ros/geometry_msgs.hpp"

#include <gtest/gtest.h>

#include "convert/test/geometry_msgs.hpp"
#include "convert/test/helpers.hpp"
#include "convert/test/instances.hpp"

TEST(point_R3d, to_from) {
    convert::test::test_to_from_eq<geometry_msgs::Point, manif::R3d>(manif::R3d());
    convert::test::test_to_from_eq<geometry_msgs::Point, manif::R3d>(manif::R3d::Identity());
    auto instances = convert::test::test_instances<manif::R3d, 100>();
    for (unsigned int i = 0; i < instances.size(); ++i) {
        convert::test::test_to_from_eq<geometry_msgs::Point>(instances[i]);
    }
}

TEST(quaternion_SO3d, to_from) {
    convert::test::test_to_from_eq<geometry_msgs::Quaternion>(manif::SO3d::Identity());
    auto instances = convert::test::test_instances<manif::SO3d, 100>();
    for (unsigned int i = 0; i < instances.size(); ++i) {
        convert::test::test_to_from_eq<geometry_msgs::Quaternion>(instances[i]);
    }
}

TEST(vector3_R3d, to_from) {
    convert::test::test_to_from_eq<geometry_msgs::Vector3, manif::R3d>(manif::R3d());
    convert::test::test_to_from_eq<geometry_msgs::Vector3, manif::R3d>(manif::R3d::Identity());
    auto instances = convert::test::test_instances<manif::R3d, 100>();
    for (unsigned int i = 0; i < instances.size(); ++i) {
        convert::test::test_to_from_eq<geometry_msgs::Vector3>(instances[i]);
    }
}

TEST(SO3d_quaternion, to_from) {
    convert::test::test_to_from_eq<manif::SO3d>(geometry_msgs::Quaternion());
    auto instances = convert::test::test_instances<geometry_msgs::Quaternion, 100>();
    for (unsigned int i = 0; i < instances.size(); ++i) {
        convert::test::check_approx(instances[i],
                convert::to<geometry_msgs::Quaternion>(convert::to<manif::SO3d>(instances[i])));
    }
}

TEST(R3d_point, to_from) {
    convert::test::test_to_from_eq<manif::R3d>(geometry_msgs::Point());
    auto instances = convert::test::test_instances<geometry_msgs::Point, 100>();
    for (unsigned int i = 0; i < instances.size(); ++i) {
        convert::test::test_to_from_eq<manif::R3d>(instances[i]);
    }
}

TEST(R3d_vector3, to_from) {
    convert::test::test_to_from_eq<manif::R3d>(geometry_msgs::Vector3());
    auto instances = convert::test::test_instances<geometry_msgs::Vector3, 100>();
    for (unsigned int i = 0; i < instances.size(); ++i) {
        convert::test::test_to_from_eq<manif::R3d>(instances[i]);
    }
}
