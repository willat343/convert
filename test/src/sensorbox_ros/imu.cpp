#include <gtest/gtest.h>

#include "convert/sensorbox_ros/sensorbox_ros.hpp"
#include "convert/test/helpers.hpp"
#include "convert/test/instances.hpp"

TEST(imu, to_from) {
    const sensor_msgs::Imu instance_default = sensor_msgs::Imu();
    const sensor_msgs::Imu to_from_default =
            convert::to<sensor_msgs::Imu>(convert::to<sensorbox::ImuMeasurement<3>>(sensor_msgs::Imu()));
    EXPECT_EQ(instance_default.header, to_from_default.header);
    EXPECT_EQ(instance_default.angular_velocity, to_from_default.angular_velocity);
    EXPECT_EQ(instance_default.linear_acceleration, to_from_default.linear_acceleration);
    const auto instances = convert::test::test_instances<sensor_msgs::Imu, 100>();
    for (unsigned int i = 0; i < instances.size(); ++i) {
        const sensor_msgs::Imu to_from =
                convert::to<sensor_msgs::Imu>(convert::to<sensorbox::ImuMeasurement<3>>(instances[i]));
        EXPECT_EQ(instances[i].header, to_from.header);
        EXPECT_EQ(instances[i].angular_velocity, to_from.angular_velocity);
        EXPECT_EQ(instances[i].linear_acceleration, to_from.linear_acceleration);
    }
}
