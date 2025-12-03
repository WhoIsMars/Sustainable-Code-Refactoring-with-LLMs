#include "bob.h"
#include <cctype>
#include <string>

using namespace std;

namespace bob {
	bool no_letter(const string& str) {
		for (char ch : str) {
			if (isalpha(ch)) return false;
		}
		return true;
	}

	bool is_all_capitals(const string& str) {
		bool has_letter = false;
		for (char ch : str) {
			if (islower(ch)) return false;
			if (isupper(ch)) has_letter = true;
		}
		return has_letter;
	}

	bool is_empty(const string& str) {
		for (char ch : str) {
			if (!isspace(ch)) return false;
		}
		return true;
	}

	bool is_question(const string& str) {
		for (auto it = str.rbegin(); it != str.rend(); ++it) {
			if (!isspace(*it)) {
				return *it == '?';
			}
		}
		return false;
	}

	string hey(const string& str) {
		if (str.empty() || is_empty(str)) return "Fine. Be that way!";
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