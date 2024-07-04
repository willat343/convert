#include "convert/ros/geometry_msgs_nav_msgs.hpp"

namespace convert {

void to(const nav_msgs::Odometry& from_msg, geometry_msgs::PoseStamped& to_msg) {
    to_msg.header = from_msg.header;
    to_msg.pose = from_msg.pose.pose;
}

}
