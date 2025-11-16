#include "gigasecond.h"

namespace gigasecond {
	ptime advance(ptime time) {
		static const seconds gigasecond(1'000'000'000);
		return time + gigasecond;
	}
} // namespace gigasecond