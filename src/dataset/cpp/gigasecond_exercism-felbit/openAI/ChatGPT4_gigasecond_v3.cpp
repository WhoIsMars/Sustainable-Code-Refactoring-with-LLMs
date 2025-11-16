#include "gigasecond.h"

namespace gigasecond
{
    constexpr long GIGASECOND = 1000000000;

    boost::posix_time::ptime advance(const boost::posix_time::ptime& begin)
    {
        static const boost::posix_time::time_duration gigasecond_duration = boost::posix_time::seconds(GIGASECOND);
        return begin + gigasecond_duration;
    }
}