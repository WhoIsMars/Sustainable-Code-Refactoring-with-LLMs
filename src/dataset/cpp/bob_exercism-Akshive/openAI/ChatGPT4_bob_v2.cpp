#include "bob.h"
#include <cctype>
#include <algorithm>

using namespace std;

namespace bob {
	bool no_letter(const string& str) {
		return none_of(str.begin(), str.end(), [](char c) {
			return isalpha(c);
		});
	}

	bool is_all_capitals(const string& str) {
		if (no_letter(str)) {
			return false;
		}
		return all_of(str.begin(), str.end(), [](char c) {
			return !islower(c) || !isalpha(c);
		});
	}

	bool is_empty(const string& str) {
		return all_of(str.begin(), str.end(), [](char c) {
			return isspace(c);
		});
	}

	bool is_question(const string& str) {
		auto it = find_if_not(str.rbegin(), str.rend(), isspace);
		return it != str.rend() && *it == '?';
	}

	string hey(const string& str) {
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