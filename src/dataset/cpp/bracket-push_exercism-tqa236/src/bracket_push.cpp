#include "bracket_push.h"

#include <algorithm>
#include <vector>

using std::remove_if;
using std::string;
using std::vector;

bool bracket_push::check(string phrase) {
  phrase.erase(remove_if(phrase.begin(), phrase.end(),
                         [](char c) {
                           string all_brackets = "()[]{}";
                           return !(all_brackets.find(c) != string::npos);
                         }),
               phrase.end());

  vector<string> brackets = {"()", "[]", "{}"};
  bool stop = false;
  while (!stop) {
    stop = true;
    for (auto const& bracket : brackets) {
      size_t position = phrase.find(bracket);
      if (position != string::npos) {
        stop = false;
        phrase.replace(position, bracket.length(), "");
      }
    }
  }
  return phrase == "";
}
