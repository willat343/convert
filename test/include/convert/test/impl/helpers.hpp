#ifndef CONVERT_IMPL_TEST_HELPERS_HPP
#define CONVERT_IMPL_TEST_HELPERS_HPP

#include <gtest/gtest.h>

#include "convert/convert.hpp"
#include "convert/test/helpers.hpp"

namespace convert::test {

template<typename ToType, typename FromType>
inline void test_to_from_eq(const FromType& in) {
    EXPECT_EQ(in, to<FromType>(to<ToType>(in)));
}

template<typename ToType, typename FromType>
inline void test_to_from_is_approx(const FromType& in) {
    EXPECT_TRUE(in.isApprox(to<FromType>(to<ToType>(in))));
}

}

#endif
