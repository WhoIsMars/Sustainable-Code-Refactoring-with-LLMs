#include "bob.h"

std::string bob::hey(std::string text) {
  bool no_lowercase = true;
  bool has_uppercase = false;
  bool is_question = false;
  bool is_empty = true;
  
  for (const char c : text) {
    if (!std::isspace(c)) {
      is_empty = false;
      if (c == '?') {
        is_question = true;
      } else {
        is_question = false;
      }
    }
    if (std::islower(c)) {
      no_lowercase = false;
    } else if (std::isupper(c)) {
      has_uppercase = true;
    }
  }
  
  if (is_empty) {
    return "Fine. Be that way!";
  }
  
  const bool is_yelling = no_lowercase && has_uppercase;
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