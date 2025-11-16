#pragma once

#include <string>

namespace rotational_cipher {

using std::string;

static const char ALPHA_LOWER {'a'};
static const char ALPHA_UPPER {'A'};
static const int  ALPHABET {26};

auto rotate(const string&, int) noexcept -> string;

}  // namespace rotational_cipher

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif