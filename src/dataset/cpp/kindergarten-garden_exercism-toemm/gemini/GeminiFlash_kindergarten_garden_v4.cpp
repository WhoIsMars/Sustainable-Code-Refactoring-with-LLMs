#include "kindergarten_garden.h"

#include <algorithm>
#include <array>

namespace kindergarten_garden {

constexpr int FLOWERS_PER_STUDENT = 2;

std::array<Plants, 4> plants(std::string_view flowers, std::string_view student) {
    const int student_index = student[0] - 'A';
    const int start_index = FLOWERS_PER_STUDENT * student_index;
    const size_t row_length = flowers.size() / 2;

    std::array<Plants, 4> out;
    out[0] = static_cast<Plants>(flowers[start_index]);
    out[1] = static_cast<Plants>(flowers[start_index + 1]);
    out[2] = static_cast<Plants>(flowers[row_length + start_index]);
    out[3] = static_cast<Plants>(flowers[row_length + start_index + 1]);

    return out;
}

}  // namespace kindergarten_garden