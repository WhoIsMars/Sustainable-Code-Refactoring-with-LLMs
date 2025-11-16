#include "gigasecond.h"

#include "boost/date_time/posix_time/posix_time.hpp"

using namespace boost::posix_time;

namespace gigasecond {

ptime advance(const ptime& time) {
    return time + seconds(1'000'000'000);
}

}  // namespace gigasecond