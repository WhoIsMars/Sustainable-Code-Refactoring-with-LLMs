#include "binary.h"

#include <algorithm>
#include <stdexcept>

namespace binary {

	int convert(const std::string& binary_str) {
		int decimal = 0;
		int power_of_two = 1;

		for (auto it = binary_str.rbegin(); it != binary_str.rend(); ++it) {
			if (*it == '1') {
				decimal += power_of_two;
				if (decimal < 0) return 0; //Prevent overflow
			} else if (*it != '0') {
				return 0;
			}
			
			if (power_of_two > INT_MAX / 2) return 0; //Prevent overflow
			power_of_two *= 2;
		}

		return decimal;
	}
} // namespace binary