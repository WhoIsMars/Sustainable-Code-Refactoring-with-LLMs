#include "bob.h"
#include <algorithm>

std::string bob::hey(std::string text) {
  // Trim leading and trailing whitespace
  text.erase(0, text.find_first_not_of(" \t\n\r\f\v"));
  text.erase(text.find_last_not_of(" \t\n\r\f\v") + 1);

  if (text.empty()) {
    return "Fine. Be that way!";
  }

  bool is_yelling = false;
  bool is_question = false;
  bool has_letters = false;

  for (size_t i = 0; i < text.length(); ++i) {
    if (std::isalpha(text[i])) {
      has_letters = true;
      if (std::islower(text[i])) {
        is_yelling = false;
        break; // No need to check further if lowercase is found
      } else {
        is_yelling = true; // Assume yelling until proven otherwise
      }
    }
  }

  if (has_letters && is_yelling) {
    is_yelling = true;
    for(char c : text){
        if(std::islower(c)){
            is_yelling = false;
            break;
        }
    }
  } else {
    is_yelling = false;
  }

  if (!text.empty() && text.back() == '?') {
    is_question = true;
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