#include "kindergarten_garden.h"

#include <algorithm>

namespace kindergarten_garden {

constexpr int FLOWERS_PER_STUDENT = 2;

std::array<Plants, 4> plants(std::string_view flowers, std::string_view student) {

    const int students_index = FLOWERS_PER_STUDENT * (student[0] - 'A');

    const std::array<char, 4> positions{flowers[students_index], flowers[students_index + 1],
                flowers[flowers.size() / 2 + 1 + students_index], flowers[flowers.size() / 2 + 1 + students_index + 1]};

    std::array<Plants, 4> out;

    std::transform(positions.begin(), positions.end(), out.begin(), [] (auto ch) {
        return static_cast<Plants>(ch);
    });

    return out;



}



}  // namespace kindergarten_garden
