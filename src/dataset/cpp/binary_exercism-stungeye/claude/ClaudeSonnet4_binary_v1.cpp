#include "binary.h"

namespace binary {

	int convert(const std::string& binary) {
		const auto length = binary.length();
		auto decimal = 0;

		for (size_t i = 0; i < length; ++i) {
			const char bit = binary[length - 1 - i];
			
			if (bit == '1') {
				decimal += (1 << i);
			} else if (bit != '0') {
				// Invalid character detected.
				return 0;
			}
		}

		return decimal;
	}
} // namespace binary