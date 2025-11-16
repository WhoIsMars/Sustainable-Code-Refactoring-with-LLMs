#include "binary.h"

#include <string>

namespace binary {

	int convert(const std::string& binary) {
		int decimal = 0;
		int power_of_two = 1;

		for (auto it = binary.rbegin(); it != binary.rend(); ++it) {
			const char bit = *it;

			if (bit == '1') {
				decimal += power_of_two;
				if (decimal < 0) return 0; // Handle potential overflow
			} else if (bit != '0') {
				return 0;
			}

			if (power_of_two > INT_MAX / 2) return 0; // Prevent overflow in power_of_two
			power_of_two *= 2;
		}

		return decimal;
	}
} // namespace binary