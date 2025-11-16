#include "reverse_string.h"
#include <string>
#include <algorithm>

namespace reverse_string {
	std::string reverse_string(std::string word) {
		std::reverse(word.begin(), word.end());
		return word;
	}
}  // namespace reverse_string