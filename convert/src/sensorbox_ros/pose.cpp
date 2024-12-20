#include "convert/sensorbox_ros/pose.hpp"

#include "convert/eigen_ros/eigen_ros.hpp"
#include "convert/ros/ros.hpp"

namespace convert {

void to(const geometry_msgs::PoseStamped& msg, sensorbox::PoseMeasurement<3>& pose) {
    to(msg.header, pose.timestamp(), pose.frame());
    to(msg.pose, pose.pose());
}

void to(const sensorbox::PoseMeasurement<3>& pose, geometry_msgs::PoseStamped& msg) {
    to(pose.timestamp(), pose.frame(), msg.header);
    to(pose.pose(), msg.pose);
}

void to(const geometry_msgs::TransformStamped& msg, sensorbox::PoseMeasurement<3>& pose) {
    to(msg.header, pose.timestamp(), pose.frame());
    pose.child_frame() = msg.child_frame_id;
    to(msg.transform, pose.pose());
}

void to(const sensorbox::PoseMeasurement<3>& pose, geometry_msgs::TransformStamped& msg) {
    to(pose.timestamp(), pose.frame(), msg.header);
    msg.child_frame_id = pose.child_frame();
    to(pose.pose(), msg.transform);
}

}
