#include "bob.h"

std::string bob::hey(std::string text) {
  bool has_uppercase = false;
  bool has_lowercase = false;
  bool is_question = false;
  bool has_non_space = false;
  
  for (const char c : text) {
    if (!std::isspace(c)) {
      has_non_space = true;
      if (c == '?') {
        is_question = true;
      }
    }
    if (std::islower(c)) {
      has_lowercase = true;
    } else if (std::isupper(c)) {
      has_uppercase = true;
    }
    
    if (has_uppercase && has_lowercase && has_non_space && is_question) {
      break;
    }
  }
  
  if (!has_non_space) {
    return "Fine. Be that way!";
  }
  
  const bool is_yelling = has_uppercase && !has_lowercase;
  
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