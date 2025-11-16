#include "gigasecond.h"

namespace gigasecond {
ptime advance(const ptime &time) { 
    return time + boost::posix_time::seconds(1000000000); 
}
}  // namespace gigasecond