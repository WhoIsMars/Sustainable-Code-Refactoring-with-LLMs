#include "bob.h"

std::string bob::hey(std::string text) {
  bool has_uppercase = false;
  bool is_question = false;
  bool is_empty = true;
  bool has_letter = false;

  for (size_t i = 0; i < text.length(); ++i) {
    char c = text[i];
    if (!std::isspace(c)) {
      is_empty = false;
      if (std::isupper(c)) {
        has_uppercase = true;
        has_letter = true;
      } else if (std::islower(c)) {
        has_letter = true;
      } else if (c == '?') {
        is_question = true;
      } else {
        has_letter = true;
      }
    }
  }

  if (is_empty) {
    return "Fine. Be that way!";
  }

  bool is_yelling = has_uppercase && !std::any_of(text.begin(), text.end(), ::islower) && has_letter;

  if (is_yelling && is_question) {
    return "Calm down, I know what I'm doing!";
  }

  if (is_yelling) {
    return "Whoa, chill out!";
  }

  if (text.back() == '?') {
      return "Sure.";
  }

  return "Whatever.";
}