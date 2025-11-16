#include "gigasecond.h"

#include "boost/date_time/posix_time/posix_time.hpp"

namespace {
    constexpr uint32_t gigasecond_days = 11574;
}

boost::gregorian::date
gigasecond::advance(const boost::gregorian::date& d)
{
    return d + boost::gregorian::days(gigasecond_days);
}