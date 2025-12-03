#include "bob.h"
#include <string>
#include <algorithm>

using namespace std;

namespace bob {

	string hey(string str) {
		// Trim leading and trailing whitespace
		size_t first = str.find_first_not_of(" \t\n\r");
		if (string::npos == first) {
			return "Fine. Be that way!";
		}
		size_t last = str.find_last_not_of(" \t\n\r");
		str = str.substr(first, (last - first + 1));

		if (str.empty()) {
			return "Fine. Be that way!";
		}

		bool is_question = (str.back() == '?');
		bool has_letters = false;
		bool is_all_caps = true;

		for (char c : str) {
			if (isalpha(c)) {
				has_letters = true;
				if (islower(c)) {
					is_all_caps = false;
					break;
				}
			}
		}

		if (is_question) {
			if (has_letters && is_all_caps) {
				return "Calm down, I know what I'm doing!";
			}
			return "Sure.";
		}

		if (has_letters && is_all_caps) {
			return "Whoa, chill out!";
		}

		return "Whatever.";
	}
}