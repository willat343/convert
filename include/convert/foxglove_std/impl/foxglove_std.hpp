#ifndef CONVERT_FOXGLOVE_STD_IMPL_FOXGLOVE_STD_HPP
#define CONVERT_FOXGLOVE_STD_IMPL_FOXGLOVE_STD_HPP

#include "convert/foxglove_std/foxglove_std.hpp"

namespace convert {

template<typename Clock, typename Duration = Clock::duration>
    requires(std::chrono::is_clock_v<Clock>)
void to(const std::chrono::time_point<Clock, Duration>& in, foxglove::schemas::Timestamp& out) {
    to(in.time_since_epoch(), out);
}

}

#if CONVERT_HEADER_ONLY
#include "convert/foxglove_std/impl/foxglove_std.impl.hpp"
#else
namespace convert {

extern template void to<std::chrono::steady_clock, std::chrono::steady_clock::duration>(
        const std::chrono::time_point<std::chrono::steady_clock, std::chrono::steady_clock::duration>&,
        foxglove::schemas::Timestamp&);
extern template void to<std::chrono::system_clock, std::chrono::system_clock::duration>(
        const std::chrono::time_point<std::chrono::system_clock, std::chrono::system_clock::duration>&,
        foxglove::schemas::Timestamp&);

}
#endif

#endif
