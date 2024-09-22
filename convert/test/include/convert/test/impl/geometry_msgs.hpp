#ifndef CONVERT_IMPL_GEOMETRY_MSGS_HPP
#define CONVERT_IMPL_GEOMETRY_MSGS_HPP

#include <gtest/gtest.h>

#include "convert/test/geometry_msgs.hpp"

namespace convert::test {

inline void check_approx(const geometry_msgs::Quaternion& lhs, const geometry_msgs::Quaternion rhs,
        const double precision) {
    EXPECT_NEAR(lhs.x, rhs.x, precision);
    EXPECT_NEAR(lhs.y, rhs.y, precision);
    EXPECT_NEAR(lhs.z, rhs.z, precision);
    EXPECT_NEAR(lhs.w, rhs.w, precision);
}

}

#endif
