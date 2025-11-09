#include "bob.h"
#include <algorithm>
#include <cctype>
#include <string>

using namespace std;

namespace bob {

string hey(string input) {
  string trimmed_input = input;
  trimmed_input.erase(0, trimmed_input.find_first_not_of(" \t\n\r"));
  trimmed_input.erase(trimmed_input.find_last_not_of(" \t\n\r") + 1);

  bool yelling = isYelling(trimmed_input);
  bool question = isQuestion(trimmed_input);
  bool silence = trimmed_input.empty();

  if (yelling && question) {
    return "Calm down, I know what I'm doing!";
  } else if (yelling) {
    return "Whoa, chill out!";
  } else if (question) {
    return "Sure.";
  } else if (silence) {
    return "Fine. Be that way!";
  } else {
    return "Whatever.";
  }
}

bool isQuestion(const string& input) {
  if (input.empty()) return false;
  for (int i = static_cast<int>(input.length()) - 1; i >= 0; --i) {
    if (input[i] == ' ') continue;
    return input[i] == '?';
  }
  return false;
}

bool isYelling(const string& input) {
  bool hasLetters = false;
  bool allUpper = true;

  for (char c : input) {
    if (isalpha(c)) {
      hasLetters = true;
      if (islower(c)) {
        return false;
      }
    }
  }

  return hasLetters;
}

bool isSilence(const string& input) { return input.empty(); }

} // namespace bob