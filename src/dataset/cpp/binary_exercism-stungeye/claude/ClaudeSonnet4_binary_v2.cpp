#include "binary.h"

namespace binary {

	int convert(const std::string& binary) {
		auto decimal = 0;

		for (char bit : binary) {
			if (bit == '1') {
				decimal = (decimal << 1) | 1;
			} else if (bit == '0') {
				decimal <<= 1;
			} else {
				// Invalid character detected.
				return 0;
			}
		}

		return decimal;
	}
} // namespace binary