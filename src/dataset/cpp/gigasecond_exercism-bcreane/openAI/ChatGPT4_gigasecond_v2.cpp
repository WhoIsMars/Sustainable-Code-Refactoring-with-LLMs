#include "gigasecond.h"
#include "boost/date_time/posix_time/posix_time.hpp"

namespace {
    constexpr uint64_t gigasecs = 1000000000;
    constexpr uint64_t seconds_per_day = 86400; // Directly use the constant value
};

boost::gregorian::date
gigasecond::advance(const boost::gregorian::date& d)
{
    return d + boost::gregorian::days(gigasecs / seconds_per_day);
}