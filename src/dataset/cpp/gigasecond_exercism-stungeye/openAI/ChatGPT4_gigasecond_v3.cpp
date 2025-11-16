#include "gigasecond.h"

namespace gigasecond {
	constexpr seconds gigasecond_duration(1'000'000'000);

	ptime advance(const ptime& time) noexcept {
		return time + gigasecond_duration;
	}
} // namespace gigasecond