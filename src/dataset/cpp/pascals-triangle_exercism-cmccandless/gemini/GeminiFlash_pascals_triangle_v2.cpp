#include "pascals_triangle.h"
#include <vector>

namespace pascals_triangle {

std::vector<std::vector<int>> generate_rows(int rowCount) {
  std::vector<std::vector<int>> rows;
  if (rowCount <= 0) {
    return rows;
  }

  rows.reserve(rowCount);
  rows.push_back({1});

  for (int i = 1; i < rowCount; ++i) {
    const std::vector<int>& previousRow = rows[i - 1];
    std::vector<int> currentRow;
    currentRow.reserve(i + 1);
    currentRow.push_back(1);

    for (int j = 0; j < previousRow.size() - 1; ++j) {
      currentRow.push_back(previousRow[j] + previousRow[j + 1]);
    }

    currentRow.push_back(1);
    rows.push_back(std::move(currentRow));
  }

  return rows;
}

}  // namespace pascals_triangle