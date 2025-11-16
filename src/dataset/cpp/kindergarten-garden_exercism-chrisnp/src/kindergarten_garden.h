#pragma once  

#include <array>
#include <string>

namespace kindergarten_garden {

enum class Plants : char {
    clover   = 'C',
    grass    = 'G',
    violets  = 'V',
    radishes = 'R'
};

auto plants(std::string const&, std::string const&) -> std::array<Plants, 4>;
}  // namespace kindergarten_garden

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif
