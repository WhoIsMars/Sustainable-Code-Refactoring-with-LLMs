#include "kindergarten_garden.h"

#include <array>

namespace kindergarten_garden {

constexpr int FLOWERS_PER_STUDENT = 2;

std::array<Plants, 4> plants(std::string_view flowers, std::string_view student) {
    const int student_index = student[0] - 'A';
    const int row_length = flowers.size() / 2;
    const int index = FLOWERS_PER_STUDENT * student_index;

    return {
        static_cast<Plants>(flowers[index]),
        static_cast<Plants>(flowers[index + 1]),
        static_cast<Plants>(flowers[row_length + index]),
        static_cast<Plants>(flowers[row_length + index + 1])
    };
}

}  // namespace kindergarten_garden