#include "bob.h"
#include <cctype>
#include <algorithm>

using namespace std;

namespace bob {
	bool no_letter(const string& str) {
		return none_of(str.begin(), str.end(), [](char c) { return isalpha(c); });
	}

	bool is_all_capitals(const string& str) {
		bool has_letter = false;
		for (char c : str) {
			if (islower(c)) return false;
			if (isalpha(c)) has_letter = true;
		}
		return has_letter;
	}

	bool is_empty(const string& str) {
		return all_of(str.begin(), str.end(), [](char c) { return isspace(c); });
	}

	bool is_question(const string& str) {
		auto it = find_if_not(str.rbegin(), str.rend(), isspace);
		return it != str.rend() && *it == '?';
	}

	string hey(const string& str) {
		if (str.empty() || is_empty(str)) return "Fine. Be that way!";
		bool question = is_question(str);
		bool all_caps = is_all_capitals(str);
		if (question && all_caps) return "Calm down, I know what I'm doing!";
		if (question) return "Sure.";
		if (all_caps) return "Whoa, chill out!";
		return "Whatever.";
	}
}