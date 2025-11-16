#pragma once

#include <string>

namespace scrabble_score {

static const int LETTER_SCORES[] 
{ 
  1, 3, 3, 2, 
  1, 4, 2, 4, 
  1, 8, 5, 1, 
  3, 1, 1, 3, 
  10, 
  1, 1, 1, 1, 
  4, 4, 8, 4, 
  10
};    

int score(const std::string&);

}  // namespace scrabble_score

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif