#include "bob.h"

#include <algorithm>
#include <cctype>

std::string bob::hey(std::string text) {
  text.erase(0, text.find_first_not_of(" \t\n\r\f\v"));
  text.erase(text.find_last_not_of(" \t\n\r\f\v") + 1);

  if (text.empty()) {
    return "Fine. Be that way!";
  }

  bool is_question = false;
  if (!text.empty() && text.back() == '?') {
    is_question = true;
  }

  bool has_letters = false;
  bool all_uppercase = true;
  for (char c : text) {
    if (std::isalpha(c)) {
      has_letters = true;
      if (std::islower(c)) {
        all_uppercase = false;
        break;
      }
    }
  }

  bool is_yelling = has_letters && all_uppercase;

  if (is_yelling && is_question) {
    return "Calm down, I know what I'm doing!";
  }

  if (is_yelling) {
    return "Whoa, chill out!";
  }

  if (is_question) {
    return "Sure.";
  }

  return "Whatever.";
}