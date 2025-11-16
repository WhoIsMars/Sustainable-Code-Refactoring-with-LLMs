#include "kindergarten_garden.h"

namespace kindergarten_garden {

constexpr int FLOWERS_PER_STUDENT = 2;

std::array<Plants, 4> plants(std::string_view flowers, std::string_view student) {
    const int students_index = FLOWERS_PER_STUDENT * (student[0] - 'A');
    const int second_row_offset = flowers.size() / 2 + students_index;

    return {
        static_cast<Plants>(flowers[students_index]),
        static_cast<Plants>(flowers[students_index + 1]),
        static_cast<Plants>(flowers[second_row_offset]),
        static_cast<Plants>(flowers[second_row_offset + 1])
    };
}

}  // namespace kindergarten_garden