#include "gigasecond.h"

namespace gigasecond
{
    boost::posix_time::ptime advance(const boost::posix_time::ptime& begin)
    {
        static const boost::posix_time::seconds gigasecond_duration(1000000000);
        return begin + gigasecond_duration;
    }
}