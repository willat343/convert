#include "convert/sensorbox_ros/pose_twist.hpp"

#include "convert/eigen_ros/eigen_ros.hpp"
#include "convert/ros/ros.hpp"

namespace convert {

void to(const nav_msgs::Odometry& msg, sensorbox::PoseTwistMeasurement<3>& pose_twist) {
    to(msg.header, pose_twist.timestamp(), pose_twist.frame());
    pose_twist.child_frame() = msg.child_frame_id;
    to(msg.pose.pose, pose_twist.pose());
    to(msg.twist.twist, pose_twist.twist());
}

void to(const sensorbox::PoseTwistMeasurement<3>& pose_twist, nav_msgs::Odometry& msg) {
    to(pose_twist.timestamp(), pose_twist.frame(), msg.header);
    msg.child_frame_id = pose_twist.child_frame();
    to(pose_twist.pose(), msg.pose.pose);
    to(pose_twist.twist(), msg.twist.twist);
}

}
