#pragma once

#include <string>

namespace pangram {

constexpr int ALPHABET_SIZE { 26 };

constexpr auto letter_idx(char ch) noexcept -> int {
    return tolower(ch) - 'a';
}

bool is_pangram(const std::string &) noexcept;

}  // namespace pangram

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif
