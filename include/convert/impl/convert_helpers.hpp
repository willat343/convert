#ifndef CONVERT_IMPL_CONVERT_HELPERS_HPP
#define CONVERT_IMPL_CONVERT_HELPERS_HPP

#include "convert/convert_helpers.hpp"

namespace convert {

template<typename ToType, typename FromType>
inline ToType to(const FromType& from) {
    ToType out;
    to(from, out);
    return out;
}

template<typename ToType, typename From1Type, typename From2Type>
inline ToType to(const From1Type& from1, const From2Type& from2) {
    ToType out;
    to(from1, from2, out);
    return out;
}

template<typename ToType, typename FromType>
inline void to_for_each_in(const std::vector<FromType>& from, std::vector<ToType>& out) {
    out.resize(from.size());
    std::transform(from.cbegin(), from.cend(), out.begin(),
            [](const FromType& from_element) { return convert::to<ToType>(from_element); });
}

template<typename ToType, typename FromType>
inline std::vector<ToType> to_for_each_in(const std::vector<FromType>& from) {
    std::vector<ToType> out;
    to_for_each_in<ToType, FromType>(from, out);
    return out;
}

template<typename ToType, typename FromType>
inline void to_optional(const std::optional<FromType>& from, std::optional<ToType>& out) {
    out = from ? std::optional<ToType>(to<ToType, FromType>(*from)) : std::nullopt;
}

template<typename ToType, typename FromType>
inline std::optional<ToType> to_optional(const std::optional<FromType>& from) {
    std::optional<ToType> out;
    to_optional<ToType, FromType>(from, out);
    return out;
}

}

#endif
