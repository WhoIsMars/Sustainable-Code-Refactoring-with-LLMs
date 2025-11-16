#include "binary.h"

#include <string>

namespace binary {

	int convert(const std::string& binary) {
		int decimal = 0;
		size_t length = binary.length();

		for (size_t i = 0; i < length; ++i) {
			char bit = binary[length - 1 - i];

			if (bit == '1') {
				decimal += (1 << i);
			} else if (bit != '0') {
				return 0;
			}
		}

		return decimal;
	}
} // namespace binary