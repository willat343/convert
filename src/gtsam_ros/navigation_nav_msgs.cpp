#include "convert/gtsam_ros/navigation_nav_msgs.hpp"
#include "convert/gtsam_ros/geometry_geometry_msgs.hpp"
#include "convert/eigen_ros/geometry_msgs.hpp"

namespace convert {

void to(const nav_msgs::Odometry& msg, gtsam::NavState& navstate){
    gtsam::Pose3 pose;
    to(msg.pose.pose, pose);
    Eigen::Vector3d velocity;
    to(msg.twist.twist.linear, velocity);
    navstate = gtsam::NavState{pose, velocity};
}

}
