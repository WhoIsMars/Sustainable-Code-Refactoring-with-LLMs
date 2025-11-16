#include "gigasecond.h"
#include "boost/date_time/posix_time/posix_time.hpp"
#include <cmath>

using namespace boost::posix_time;

namespace gigasecond {

	int GIGASECOND = pow(10, 9);

	ptime advance(ptime value) {
		return value + seconds(GIGASECOND);
	}
}  // namespace gigasecond
