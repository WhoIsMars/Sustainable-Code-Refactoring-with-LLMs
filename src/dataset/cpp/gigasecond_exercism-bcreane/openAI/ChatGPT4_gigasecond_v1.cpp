#include "gigasecond.h"
#include "boost/date_time/posix_time/posix_time.hpp"

namespace {
    constexpr int gigasecs = 1000000000;
    constexpr int seconds_per_day = 86400; // Precomputed constant
}

boost::gregorian::date
gigasecond::advance(const boost::gregorian::date& d)
{
    return d + boost::gregorian::days(gigasecs / seconds_per_day);
}