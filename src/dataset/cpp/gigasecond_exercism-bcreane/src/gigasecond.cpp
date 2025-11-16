#include "gigasecond.h"

#include "boost/date_time/posix_time/posix_time.hpp"

namespace {
    const uint32_t gigasecs(1000000000);
    const uint64_t seconds_per_minute = 60;
    const uint64_t seconds_per_hour = seconds_per_minute * 60;
    const uint64_t seconds_per_day = seconds_per_hour * 24;
};

boost::gregorian::date
gigasecond::advance(const boost::gregorian::date& d)
{
    return d + boost::gregorian::days(gigasecs/seconds_per_day);
}
