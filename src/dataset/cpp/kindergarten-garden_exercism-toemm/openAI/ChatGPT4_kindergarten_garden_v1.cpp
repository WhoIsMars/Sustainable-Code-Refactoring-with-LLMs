#include "kindergarten_garden.h"

#include <array>

namespace kindergarten_garden {

constexpr int FLOWERS_PER_STUDENT = 2;

std::array<Plants, 4> plants(std::string_view flowers, std::string_view student) {
    int students_index = FLOWERS_PER_STUDENT * (student[0] - 'A');
    int mid = flowers.size() / 2;

    return {
        static_cast<Plants>(flowers[students_index]),
        static_cast<Plants>(flowers[students_index + 1]),
        static_cast<Plants>(flowers[mid + students_index]),
        static_cast<Plants>(flowers[mid + students_index + 1])
    };
}

}  // namespace kindergarten_garden