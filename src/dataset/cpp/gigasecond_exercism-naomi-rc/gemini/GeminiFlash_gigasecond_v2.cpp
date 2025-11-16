#include "gigasecond.h"
#include "boost/date_time/posix_time/posix_time.hpp"

using namespace boost::posix_time;

namespace gigasecond {

	const long long GIGASECOND = 1000000000LL;

	ptime advance(ptime value) {
		return value + seconds(GIGASECOND);
	}
}  // namespace gigasecond