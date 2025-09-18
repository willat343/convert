#ifndef CONVERT_FOXGLOVE_STD_FOXGLOVE_STD_HPP
#define CONVERT_FOXGLOVE_STD_FOXGLOVE_STD_HPP

#include <chrono>
#include <foxglove/schemas.hpp>

namespace convert {

void to(const std::chrono::nanoseconds& in, foxglove::schemas::Duration& out);

void to(const std::chrono::nanoseconds& in, foxglove::schemas::Timestamp& out);

template<typename Clock, typename Duration = Clock::duration>
    requires(std::chrono::is_clock_v<Clock>)
void to(const std::chrono::time_point<Clock, Duration>& in, foxglove::schemas::Timestamp& out);

}

#include "convert/foxglove_std/impl/foxglove_std.hpp"

#endif
