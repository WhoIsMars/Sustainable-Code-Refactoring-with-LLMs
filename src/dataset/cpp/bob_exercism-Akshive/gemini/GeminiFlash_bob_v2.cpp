#include "bob.h"
#include <string>
#include <algorithm>

using namespace std;

namespace bob {

	bool is_empty(const string& str) {
		return all_of(str.begin(), str.end(), [](unsigned char c){ return isspace(c); });
	}

	bool is_question(const string& str) {
		for (int i = str.length() - 1; i >= 0; --i) {
			if (!isspace(str[i])) {
				return str[i] == '?';
			}
		}
		return false;
	}

	bool is_all_caps(const string& str) {
		bool has_letter = false;
		for (char c : str) {
			if (isalpha(c)) {
				has_letter = true;
				if (islower(c)) {
					return false;
				}
			}
		}
		return has_letter;
	}

	string hey(string str) {
		if (str.empty() || is_empty(str)) {
			return "Fine. Be that way!";
		}

		if (is_question(str)) {
			if (is_all_caps(str)) {
				return "Calm down, I know what I'm doing!";
			}
			return "Sure.";
		}

		if (is_all_caps(str)) {
			return "Whoa, chill out!";
		}

		return "Whatever.";
	}
}