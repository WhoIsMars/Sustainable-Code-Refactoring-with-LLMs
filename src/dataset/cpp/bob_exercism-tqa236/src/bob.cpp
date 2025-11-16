#include "bob.h"

std::string bob::hey(std::string text) {
  bool no_lowercase = true;
  bool has_uppercase = false;
  bool is_question = false;
  bool is_empty = true;
  for (char& c : text) {
    if (!std::isspace(c)) {
      is_question = false;
      is_empty = false;
    }
    if (std::islower(c)) {
      no_lowercase = false;
    }
    if (std::isupper(c)) {
      has_uppercase = true;
    }
    if (c == '?') {
      is_question = true;
    }
  }
  bool is_yelling = no_lowercase && has_uppercase;
  if (is_empty) {
    return "Fine. Be that way!";
  }
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
