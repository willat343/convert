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

}

#endif
