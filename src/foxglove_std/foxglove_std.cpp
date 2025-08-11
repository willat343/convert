#include "convert/foxglove_std/foxglove_std.hpp"

#include <cassert>

namespace convert {

void to(const std::chrono::nanoseconds& in, foxglove::schemas::Timestamp& out) {
    assert(in >= std::chrono::nanoseconds(0));
    out.sec = static_cast<uint32_t>(in / std::chrono::seconds(1));
    out.nsec = static_cast<uint32_t>(std::abs((in % std::chrono::seconds(1)) / std::chrono::nanoseconds(1)));
}

}
