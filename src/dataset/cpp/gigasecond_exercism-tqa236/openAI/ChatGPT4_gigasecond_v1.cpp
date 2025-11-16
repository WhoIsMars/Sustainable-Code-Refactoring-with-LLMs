#include "gigasecond.h"

namespace gigasecond {
constexpr long GIGASECOND = 1000000000;

ptime advance(const ptime &time) {
    return time + boost::posix_time::seconds(GIGASECOND);
}
}  // namespace gigasecond