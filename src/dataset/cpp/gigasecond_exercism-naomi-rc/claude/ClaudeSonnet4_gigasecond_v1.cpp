#include "gigasecond.h"
#include "boost/date_time/posix_time/posix_time.hpp"

using namespace boost::posix_time;

namespace gigasecond {

	constexpr int GIGASECOND = 1000000000;

	ptime advance(ptime value) {
		return value + seconds(GIGASECOND);
	}
}  // namespace gigasecond