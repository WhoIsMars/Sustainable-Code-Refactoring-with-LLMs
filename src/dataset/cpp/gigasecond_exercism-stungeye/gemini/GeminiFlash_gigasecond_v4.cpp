#include "gigasecond.h"
#include <chrono>

namespace gigasecond {
	ptime advance(ptime time) {
		static const seconds gigasecond_duration(1'000'000'000);
		return time + gigasecond_duration;
	}
} // namespace gigasecond