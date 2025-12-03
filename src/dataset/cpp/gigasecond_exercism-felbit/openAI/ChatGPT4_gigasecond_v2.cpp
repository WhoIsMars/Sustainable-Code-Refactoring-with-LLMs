#include "gigasecond.h"

namespace gigasecond
{
    constexpr long GIGASECOND = 1000000000;

    boost::posix_time::ptime advance(const boost::posix_time::ptime& begin) noexcept
    {
        return begin + boost::posix_time::seconds(GIGASECOND);
    }
}