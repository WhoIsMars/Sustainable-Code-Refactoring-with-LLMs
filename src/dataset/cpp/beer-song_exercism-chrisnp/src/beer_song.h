#pragma once

#include <string>

namespace beer_song {

[[nodiscard, gnu::const]]
auto verse(int) noexcept -> std::string;
auto sing(int, int) noexcept -> std::string;
auto sing(int) noexcept -> std::string;

}  // namespace beer_song


#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif