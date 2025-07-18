#ifndef CONVERT_SENSORBOX_ROS_IMU_HPP
#define CONVERT_SENSORBOX_ROS_IMU_HPP

#include <sensor_msgs/Imu.h>

#include <sensorbox/imu.hpp>

namespace convert {

void to(const sensor_msgs::Imu& msg, sensorbox::ImuMeasurement<3>& imu);

void to(const sensorbox::ImuMeasurement<3>& imu, sensor_msgs::Imu& msg);

}

#endif
