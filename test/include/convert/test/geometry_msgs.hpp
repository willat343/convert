#ifndef CONVERT_GEOMETRY_MSGS_HPP
#define CONVERT_GEOMETRY_MSGS_HPP

#include <geometry_msgs/Quaternion.h>

namespace convert::test {

void check_approx(const geometry_msgs::Quaternion& lhs, const geometry_msgs::Quaternion rhs,
        const double precision = 1.0e-12);

}

#include "convert/test/impl/geometry_msgs.hpp"

#endif
