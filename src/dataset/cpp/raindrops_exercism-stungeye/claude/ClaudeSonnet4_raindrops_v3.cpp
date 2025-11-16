#include "raindrops.h"

namespace raindrops {

	std::string convert(int number) {
		std::string raindrops;
		raindrops.reserve(15);

		const bool div3 = (number % 3 == 0);
		const bool div5 = (number % 5 == 0);
		const bool div7 = (number % 7 == 0);

		if (div3) {
			raindrops += "Pling";
		}

		if (div5) {
			raindrops += "Plang";
		}

		if (div7) {
			raindrops += "Plong";
		}

		return (div3 | div5 | div7) ? raindrops : std::to_string(number);
	}
} // namespace raindrops