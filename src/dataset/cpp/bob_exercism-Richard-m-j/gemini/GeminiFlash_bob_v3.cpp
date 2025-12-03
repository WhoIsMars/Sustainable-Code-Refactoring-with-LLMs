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
  if (isYelling(input) && isQuestion(input)) {
    return "Calm down, I know what I'm doing!";
  }
  if (isYelling(input)) {
    return "Whoa, chill out!";
  }
  if (isQuestion(input)) {
    return "Sure.";
  }
  return "Whatever.";
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
        return false;
      }
    }
  }
  return hasLetters;
}

bool isSilence(const string& input) {
  return all_of(input.begin(), input.end(), [](unsigned char c) {
    return isspace(c);
  });
}

}  // namespace bob