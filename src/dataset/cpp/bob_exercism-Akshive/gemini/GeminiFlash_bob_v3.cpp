#include "bob.h"
#include <string>
#include <algorithm>

using namespace std;

namespace bob {

	bool no_letter(const string& str) {
		for (char c : str) {
			if (isalpha(c)) {
				return false;
			}
		}
		return true;
	}

	bool is_all_capitals(const string& str) {
		if (no_letter(str)) {
			return false;
		}
		for (char c : str) {
			if (islower(c)) {
				return false;
			}
		}
		return true;
	}

	bool is_empty(const string& str) {
		for (char c : str) {
			if (!isspace(c)) {
				return false;
			}
		}
		return true;
	}

	bool is_question(const string& str) {
		for (int i = str.size() - 1; i >= 0; --i) {
			if (!isspace(str[i])) {
				return str[i] == '?';
			}
		}
		return false;
	}

	string hey(string str) {
		if (str.empty() || is_empty(str)) {
			return "Fine. Be that way!";
		}
		if (is_question(str)) {
			if (is_all_capitals(str)) {
				return "Calm down, I know what I'm doing!";
			}
			return "Sure.";
		}
		if (is_all_capitals(str)) {
			return "Whoa, chill out!";
		}
		return "Whatever.";
	}
}