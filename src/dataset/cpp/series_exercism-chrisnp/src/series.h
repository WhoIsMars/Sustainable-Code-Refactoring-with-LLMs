#pragma once

#include <string>
#include <vector>

namespace series {

typedef std::vector<std::string> slices_t;
using luint_t = long unsigned int;

auto slice(std::string const &, luint_t) -> slices_t;

}  // namespace series

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif