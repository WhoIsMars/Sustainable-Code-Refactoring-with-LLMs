#include "pascals_triangle.h"

#include <vector>

namespace pascals_triangle {

Triangle generate_rows(const int number_of_rows) {
  if (number_of_rows <= 0) {
    return {};
  }

  Triangle triangle;
  triangle.reserve(number_of_rows);

  for (int row_num = 0; row_num < number_of_rows; ++row_num) {
    std::vector<int> current_row(row_num + 1, 1);

    if (row_num > 1) {
      const auto& prev_row = triangle[row_num - 1];
      for (int pos = 1; pos < row_num; ++pos) {
        current_row[pos] = prev_row[pos - 1] + prev_row[pos];
      }
    }
    triangle.push_back(current_row);
  }

  return triangle;
}

} // namespace pascals_triangle