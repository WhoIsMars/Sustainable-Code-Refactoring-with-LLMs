#include "gigasecond.h"

using boost::posix_time::seconds;

namespace gigasecond {
ptime advance(const ptime &time) { return time + seconds(1000000000); }
}  // namespace gigasecond
