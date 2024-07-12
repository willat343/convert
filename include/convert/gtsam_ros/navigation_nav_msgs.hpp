#ifndef CONVERT_GTSAM_ROS_NAVIGATION_NAV_MSGS_HPP
#define CONVERT_GTSAM_ROS_NAVIGATION_NAV_MSGS_HPP

#include <gtsam/navigation/NavState.h>
#include <nav_msgs/Odometry.h>

namespace convert {

/**
 * @brief Convert odometry message to navstate.
 * 
 * Only pose and linear velocity are copied. The header, child frame id, angular velocity and all covariances are lost.
 * 
 * @param msg 
 * @param navstate 
 */
void to(const nav_msgs::Odometry& msg, gtsam::NavState& navstate);

}

#endif
