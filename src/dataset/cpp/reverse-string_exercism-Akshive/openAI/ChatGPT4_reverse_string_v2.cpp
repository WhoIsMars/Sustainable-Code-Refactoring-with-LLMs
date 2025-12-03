#include "reverse_string.h"
#include <algorithm>

namespace reverse_string {

	string reverse_string(string sentence) {
		std::reverse(sentence.begin(), sentence.end());
		return sentence;
	}

}