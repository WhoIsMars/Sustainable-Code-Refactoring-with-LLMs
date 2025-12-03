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

bool isQuestion(string input) {
  size_t i = input.length();
  while (i > 0 && (input[i - 1] == ' ' || input[i - 1] == '\t')) {
    --i;
  }
  return (i > 0 && input[i - 1] == '?');
}

bool isYelling(string input) {
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

bool isSilence(string input) {
  return all_of(input.begin(), input.end(), [](unsigned char c) {
    return isspace(c);
  });
}

} // namespace bob