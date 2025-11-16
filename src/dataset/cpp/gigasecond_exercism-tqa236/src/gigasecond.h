#pragma once
#include "boost/date_time/posix_time/posix_time.hpp"

namespace gigasecond {
using boost::posix_time::ptime;
ptime advance(const ptime &);
}  // namespace gigasecond
