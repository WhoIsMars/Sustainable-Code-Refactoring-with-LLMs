#include "pascals_triangle.h"

#include <vector>

std::vector<std::vector<int>> pascals_triangle::generate_rows(int num_row) {
  std::vector<std::vector<int>> rows;
  if (num_row <= 0) {
    return rows;
  }
  rows.reserve(num_row); // Reserve memory upfront to avoid reallocations
  rows.push_back({1});
  for (int i = 1; i < num_row; ++i) {
    std::vector<int> row(i + 1, 1); // Initialize row with 1s
    const std::vector<int>& prev_row = rows.back();
    for (int j = 1; j < i; ++j) {
      row[j] = prev_row[j - 1] + prev_row[j];
    }
    rows.push_back(std::move(row)); // Use move semantics to avoid copying
  }
  return rows;
}