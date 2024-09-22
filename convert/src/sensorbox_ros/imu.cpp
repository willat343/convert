#include "convert/sensorbox_ros/imu.hpp"
#include "convert/eigen_ros/eigen_ros.hpp"
#include "convert/ros/ros.hpp"

namespace convert {

void to(const sensor_msgs::Imu& msg, sensorbox::Imu& imu) {
    to(msg.header, imu.timestamp, imu.frame);
    to(msg.orientation, imu.orientation);
    to(msg.angular_velocity, imu.angular_velocity);
    to(msg.linear_acceleration, imu.linear_acceleration);
    to(msg.orientation_covariance, imu.orientation_covariance);
    to(msg.angular_velocity_covariance, imu.angular_velocity_covariance);
    to(msg.linear_acceleration_covariance, imu.linear_acceleration_covariance);

}

void to(const sensorbox::Imu& imu, sensor_msgs::Imu& msg) {
    to(imu.timestamp, imu.frame, msg.header);
    to(imu.orientation, msg.orientation);
    to(imu.angular_velocity, msg.angular_velocity);
    to(imu.linear_acceleration, msg.linear_acceleration);
    to(imu.orientation_covariance, msg.orientation_covariance);
    to(imu.angular_velocity_covariance, msg.angular_velocity_covariance);
    to(imu.linear_acceleration_covariance, msg.linear_acceleration_covariance);
}

}
