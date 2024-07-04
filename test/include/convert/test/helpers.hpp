#ifndef CONVERT_TEST_HELPERS_HPP
#define CONVERT_TEST_HELPERS_HPP

namespace convert::test {

/**
 * @brief Convert to and from a type and test for equality. Requires an equality operator to exist for FromType:
 *      bool operator==(const FromType&, const FromType&);
 *
 * @tparam ToType
 * @tparam FromType
 * @param in
 */
template<typename ToType, typename FromType>
void test_to_from_eq(const FromType& in);

/**
 * @brief Convert to and from a type and test for approximate equality. Requires the isApprox member function to be
 * defined for the FromType class:
 *      bool FromType::isApprox(const FromType&) const;
 *
 * @tparam ToType
 * @tparam FromType
 * @param in
 */
template<typename ToType, typename FromType>
void test_to_from_is_approx(const FromType& in);

}

#include "convert/test/impl/helpers.hpp"

#endif
