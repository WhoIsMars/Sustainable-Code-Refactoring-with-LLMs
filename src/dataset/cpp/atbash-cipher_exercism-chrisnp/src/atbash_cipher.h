#pragma once
#include <string>

namespace atbash_cipher {

using string = std::string;

auto encode(const string&) noexcept -> string;
auto decode(const string&) -> string;

constexpr auto alpha(const char &c) noexcept -> bool {
    return  'a' <= c && c <= 'z';
}
constexpr auto digit(const char &c) noexcept -> bool {
    return  '0' <= c && c <= '9';
}

}  // namespace atbash_cipher


#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif