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

#endif
