#include "raindrops.h"

namespace raindrops {

	std::string convert(int number) {
		bool divisible = false;
		std::string raindrops;

		if (number % 3 == 0) {
			raindrops = "Pling";
			divisible = true;
		}

		if (number % 5 == 0) {
			raindrops += "Plang";
			divisible = true;
		}

		if (number % 7 == 0) {
			raindrops += "Plong";
			divisible = true;
		}

		return divisible ? raindrops : std::to_string(number);
	}
} // namespace raindrops