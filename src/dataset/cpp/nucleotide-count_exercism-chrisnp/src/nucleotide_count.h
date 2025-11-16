#pragma once
#include <string>
#include <map>

namespace nucleotide_count {

typedef std::map<char, int> counts_t;

auto count(std::string) -> counts_t;

}  // namespace nucleotide_count

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif