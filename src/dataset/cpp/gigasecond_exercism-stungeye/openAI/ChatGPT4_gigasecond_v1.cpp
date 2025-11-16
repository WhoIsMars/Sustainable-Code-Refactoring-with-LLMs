#include "gigasecond.h"

namespace gigasecond {
	ptime advance(const ptime& time) noexcept {
		static const seconds gigasecond_duration(1'000'000'000);
		return time + gigasecond_duration;
	}
} // namespace gigasecond