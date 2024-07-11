#include "convert/sensorbox_ros/sensorbox_ros.hpp"

#include <gtest/gtest.h>

#include "convert/test/helpers.hpp"
#include "convert/test/instances.hpp"

TEST(imu, to_from) {
    convert::test::test_to_from_eq<sensorbox::Imu, sensor_msgs::Imu>(sensor_msgs::Imu());
    const auto instances = convert::test::test_instances<sensor_msgs::Imu, 100>();
    for (unsigned int i = 0; i < instances.size(); ++i) {
        convert::test::test_to_from_eq<sensorbox::Imu>(instances[i]);
    }
}
