#include "binary.h"

namespace binary {

	int convert(const std::string& binary) {
		int decimal = 0;
		int power = 1;

		for (auto it = binary.rbegin(); it != binary.rend(); ++it) {
			const char bit = *it;
			
			if (bit == '1') {
				decimal += power;
			} else if (bit != '0') {
				return 0;
			}
			
			power <<= 1;
		}

		return decimal;
	}
} // namespace binary