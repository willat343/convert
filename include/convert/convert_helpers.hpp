#ifndef CONVERT_CONVERT_HELPERS_HPP
#define CONVERT_CONVERT_HELPERS_HPP

#include <vector>

namespace convert {

/**
 * @brief Convenience function to perform a 1-to-1 conversion between types.
 *
 * Requires function `void to(const FromType&, ToType&);` to be defined and `ToType` to be default-constructable.
 *
 * Example usage:
 *      ToType msg = to<ToType>(t);
 *
 * @tparam ToType
 * @tparam FromType
 * @param from
 * @return ToType
 */
template<typename ToType, typename FromType>
ToType to(const FromType& from);

/**
 * @brief Convenience function to perform a 2-to-1 conversion between types.
 *
 * Requires function `void to(const From1Type&, const From1Type&, ToType&);` to be defined and `ToType` to be
 * default-constructable.
 *
 * @tparam ToType
 * @tparam From1Type
 * @tparam From2Type
 * @param from1
 * @param from2
 * @return ToType
 */
template<typename ToType, typename From1Type, typename From2Type>
ToType to(const From1Type& from1, const From2Type& from2);

/**
 * @brief Convenience function to perform a conversion of a vector of FromType objects to ToType objects.
 *
 * Requires function `void to(const FromType&, ToType&);` to be defined and `ToType` to be default-constructable.
 *
 * @tparam ToType
 * @tparam FromType
 * @param from
 * @return std::vector<ToType>
 */
template<typename ToType, typename FromType>
std::vector<ToType> to_for_each_in(const std::vector<FromType>& from);

}

#include "convert/impl/convert_helpers.hpp"

#endif
