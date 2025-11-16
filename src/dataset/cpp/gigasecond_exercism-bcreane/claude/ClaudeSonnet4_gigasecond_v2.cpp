#include "gigasecond.h"

#include "boost/date_time/posix_time/posix_time.hpp"

namespace {
    constexpr uint32_t gigasec_days = 11574; // 1000000000 / 86400 precomputed
}

boost::gregorian::date
gigasecond::advance(const boost::gregorian::date& d)
{
    return d + boost::gregorian::days(gigasec_days);
}