#include "gigasecond.h"

#include "boost/date_time/posix_time/posix_time.hpp"

namespace {
    constexpr uint32_t gigasecs = 1000000000;
    constexpr uint32_t seconds_per_day = 86400;
    constexpr uint32_t days_in_gigasecond = gigasecs / seconds_per_day;
}

boost::gregorian::date
gigasecond::advance(const boost::gregorian::date& d)
{
    return d + boost::gregorian::days(days_in_gigasecond);
}