#include "raindrops.h"

namespace raindrops {

	std::string convert(int number) {
		bool divisible_by_3 = (number % 3 == 0);
		bool divisible_by_5 = (number % 5 == 0);
		bool divisible_by_7 = (number % 7 == 0);

		if (!divisible_by_3 && !divisible_by_5 && !divisible_by_7) {
			return std::to_string(number);
		}

		std::string raindrops;
		if (divisible_by_3) raindrops = "Pling";
		if (divisible_by_5) raindrops += "Plang";
		if (divisible_by_7) raindrops += "Plong";

		return raindrops;
	}
} // namespace raindrops