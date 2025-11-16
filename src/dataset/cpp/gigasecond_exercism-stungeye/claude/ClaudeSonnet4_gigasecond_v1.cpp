#include "gigasecond.h"

namespace gigasecond {
	ptime advance(ptime time) {
		constexpr auto gigasecond_duration = seconds(1'000'000'000);
		return time + gigasecond_duration;
	}
} // namespace gigasecond