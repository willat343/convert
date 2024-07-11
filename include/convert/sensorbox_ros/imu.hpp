#ifndef CONVERT_SENSORBOX_ROS_IMU_HPP
#define CONVERT_SENSORBOX_ROS_IMU_HPP

#include <sensor_msgs/Imu.h>

#include <sensorbox/imu.hpp>

namespace convert {

void to(const sensor_msgs::Imu& msg, sensorbox::Imu& imu);

void to(const sensorbox::Imu& imu, sensor_msgs::Imu& msg);

}

#endif
