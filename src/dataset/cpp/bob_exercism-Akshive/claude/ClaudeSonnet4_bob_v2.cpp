#include "bob.h"
#include <cctype>
#include <string>

using namespace std;

namespace bob {
	string hey(const string& str) {
		if (str.empty()) return "Fine. Be that way!";
		
		bool has_letter = false;
		bool has_lowercase = false;
		bool is_question = false;
		bool is_empty_content = true;
		
		// Single pass through the string
		for (int i = 0; i < static_cast<int>(str.size()); ++i) {
			char c = str[i];
			
			if (c != ' ' && c != '\t' && c != '\n' && c != '\r') {
				is_empty_content = false;
			}
			
			if (isalpha(c)) {
				has_letter = true;
				if (islower(c)) {
					has_lowercase = true;
				}
			}
		}
		
		// Check if it's a question by looking at the last non-whitespace character
		for (int i = str.size() - 1; i >= 0; --i) {
			if (str[i] != ' ') {
				is_question = (str[i] == '?');
				break;
			}
		}
		
		if (is_empty_content) return "Fine. Be that way!";
		
		bool is_all_caps = has_letter && !has_lowercase;
		
		if (is_question) {
			return is_all_caps ? "Calm down, I know what I'm doing!" : "Sure.";
		}
		
		return is_all_caps ? "Whoa, chill out!" : "Whatever.";
	}
}