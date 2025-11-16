#include "gigasecond.h"

namespace gigasecond {
constexpr int64_t GIGASECOND = 1000000000;

ptime advance(const ptime &time) noexcept {
    return time + boost::posix_time::seconds(GIGASECOND);
}
}  // namespace gigasecond