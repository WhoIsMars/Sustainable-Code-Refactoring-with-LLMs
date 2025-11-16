#include "gigasecond.h"

#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

boost::posix_time::ptime advance(const boost::posix_time::ptime& time) {
    return time + boost::posix_time::seconds(1'000'000'000);
}

}  // namespace gigasecond