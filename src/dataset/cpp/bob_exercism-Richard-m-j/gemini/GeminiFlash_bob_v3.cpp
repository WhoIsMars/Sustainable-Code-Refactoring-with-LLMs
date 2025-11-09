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
  } else if (yelling) {
    return "Whoa, chill out!";
  } else if (question) {
    return "Sure.";
  } else {
    return "Whatever.";
  }
}

bool isQuestion(const string& input) {
  size_t i = input.length();
  while (i > 0) {
    --i;
    if (input[i] == ' ' || input[i] == '\t') {
      continue;
    } else if (input[i] == '?') {
      return true;
    } else {
      return false;
    }
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
        allUpper = false;
        break;
      }
    }
  }

  return hasLetters && allUpper;
}

bool isSilence(const string& input) {
  return all_of(input.begin(), input.end(), [](unsigned char c) {
    return isspace(c);
  });
}

} // namespace bob