#include "convert/sensorbox_ros/imu.hpp"

#include "convert/eigen_ros/eigen_ros.hpp"
#include "convert/ros/ros.hpp"

namespace convert {

void to(const sensor_msgs::Imu& msg, sensorbox::ImuMeasurement<3>& imu) {
    to(msg.header, imu.timestamp(), imu.frame());
    imu.child_frame() = imu.frame();
    to(msg.angular_velocity, imu.angular_velocity());
    to(msg.linear_acceleration, imu.linear_acceleration());
}

void to(const sensorbox::ImuMeasurement<3>& imu, sensor_msgs::Imu& msg) {
    to(imu.timestamp(), imu.frame(), msg.header);
    msg.orientation_covariance[0] = -1.0;
    to(imu.angular_velocity(), msg.angular_velocity);
    to(imu.linear_acceleration(), msg.linear_acceleration);
}

}
