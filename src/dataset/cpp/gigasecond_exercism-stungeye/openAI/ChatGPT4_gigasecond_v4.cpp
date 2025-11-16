#include "gigasecond.h"

namespace gigasecond {
	constexpr seconds GIGASECOND(1'000'000'000);
	
	ptime advance(const ptime& time) noexcept {
		return time + GIGASECOND;
	}
} // namespace gigasecond