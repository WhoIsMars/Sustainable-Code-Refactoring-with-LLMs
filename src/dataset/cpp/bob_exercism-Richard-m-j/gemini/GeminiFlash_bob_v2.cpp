#include "bob.h"
#include <algorithm>
#include <cctype>
#include <string>

using namespace std;

namespace bob {

string hey(string input) {
  if (isSilence(input)) {
    return "Fine. Be that way!";
  }

  bool yelling = isYelling(input);
  bool question = isQuestion(input);

  if (yelling && question) {
    return "Calm down, I know what I'm doing!";
  }

  if (yelling) {
    return "Whoa, chill out!";
  }

  if (question) {
    return "Sure.";
  }

  return "Whatever.";
}

bool isQuestion(const string& input) {
  for (int i = input.length() - 1; i >= 0; --i) {
    if (input[i] == ' ') continue;
    return input[i] == '?';
  }
  return false;
}

bool isYelling(const string& input) {
  bool hasLetters = false;
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

bool isSilence(const string& input) {
  for (char c : input) {
    if (!isspace(c)) {
      return false;
    }
  }
  return true;
}

} // namespace bob