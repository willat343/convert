#ifndef CONVERT_FOXGLOVE_STD_IMPL_FOXGLOVE_STD_IMPL_HPP
#define CONVERT_FOXGLOVE_STD_IMPL_FOXGLOVE_STD_IMPL_HPP

#include <cassert>

#include "convert/foxglove_std/impl/foxglove_std.hpp"
#include "convert/impl/convert.hpp"

namespace convert {

CONVERT_INLINE void to(const std::chrono::nanoseconds& in, foxglove::schemas::Duration& out) {
    assert(in >= std::chrono::nanoseconds(0));
    out.sec = static_cast<uint32_t>(in / std::chrono::seconds(1));
    out.nsec = static_cast<uint32_t>(std::abs((in % std::chrono::seconds(1)) / std::chrono::nanoseconds(1)));
}

CONVERT_INLINE void to(const std::chrono::nanoseconds& in, foxglove::schemas::Timestamp& out) {
    assert(in >= std::chrono::nanoseconds(0));
    out.sec = static_cast<uint32_t>(in / std::chrono::seconds(1));
    out.nsec = static_cast<uint32_t>(std::abs((in % std::chrono::seconds(1)) / std::chrono::nanoseconds(1)));
}

}

#endif
