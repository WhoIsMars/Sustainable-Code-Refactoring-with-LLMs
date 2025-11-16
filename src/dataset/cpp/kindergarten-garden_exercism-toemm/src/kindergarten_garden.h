#pragma once

#include <array>
#include <string>

namespace kindergarten_garden {

enum class Plants : char {
    radishes = 'R',
    clover = 'C',
    violets = 'V',
    grass = 'G',
};

std::array<Plants, 4> plants(std::string_view flowers, std::string_view student);


}  // namespace kindergarten_garden
