#include "gigasecond.h"

#include <string>
#include "boost/date_time/posix_time/posix_time.hpp"

using namespace boost::posix_time;


namespace gigasecond {


ptime advance(ptime time) {

    ptime new_time = time + seconds(1'000'000'000);
    std::cout << new_time << std::endl;
    return new_time;
}

}  // namespace gigasecond
