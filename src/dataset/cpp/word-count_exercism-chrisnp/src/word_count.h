#pragma once
#include <map>
#include <string>

namespace word_count {

typedef std::map<std::string, int> words_map_t;
const words_map_t words(const std::string&);

}  // namespace word_count

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif