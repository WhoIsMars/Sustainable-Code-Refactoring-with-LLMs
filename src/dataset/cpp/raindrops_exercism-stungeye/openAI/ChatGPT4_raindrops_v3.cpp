#include "raindrops.h"

namespace raindrops {

	std::string convert(int number) {
		bool hasFactor = false;
		std::string raindrops;

		if (number % 3 == 0) {
			raindrops = "Pling";
			hasFactor = true;
		}

		if (number % 5 == 0) {
			raindrops += "Plang";
			hasFactor = true;
		}

		if (number % 7 == 0) {
			raindrops += "Plong";
			hasFactor = true;
		}

		return hasFactor ? raindrops : std::to_string(number);
	}
} // namespace raindrops