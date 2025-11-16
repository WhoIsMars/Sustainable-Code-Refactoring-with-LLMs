#include "gigasecond.h"

#include <string>
#include "boost/date_time/posix_time/posix_time.hpp"

using namespace boost::posix_time;


namespace gigasecond {


ptime advance(ptime time) {

    static const seconds gigasecond(1000000000);
    ptime new_time = time + gigasecond;
    return new_time;
}

}  // namespace gigasecond