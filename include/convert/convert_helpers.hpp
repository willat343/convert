#ifndef CONVERT_CONVERT_HELPERS_HPP
#define CONVERT_CONVERT_HELPERS_HPP

namespace convert {

/**
 * @brief Convenience function to convert between types. Requires the function `void to(const FromType&, ToType&);` to
 * be defined and for `ToType` to be default-constructable.
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
inline ToType to(const FromType& from);

}

#include "convert/impl/convert_helpers.hpp"

#endif
