#ifndef CONVERT_IMPL_CONVERT_HELPERS_HPP
#define CONVERT_IMPL_CONVERT_HELPERS_HPP

#include "convert/convert_helpers.hpp"

namespace convert {

template<typename ToType, typename FromType>
inline ToType to(const FromType& in) {
    ToType out;
    to(in, out);
    return out;
}

}

#endif
