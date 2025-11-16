#include "pascals_triangle.h"

std::vector<std::vector<int>> pascals_triangle::generate_rows(int num_row) {
  if (num_row == 0) {
    return {};
  }
  
  std::vector<std::vector<int>> rows;
  rows.reserve(num_row);
  
  rows.push_back({1});
  
  for (int i = 1; i < num_row; i++) {
    std::vector<int> row;
    row.reserve(i + 1);
    row.push_back(1);
    
    const auto& prev_row = rows[i - 1];
    for (int j = 1; j < i; j++) {
      row.push_back(prev_row[j - 1] + prev_row[j]);
    }
    
    row.push_back(1);
    rows.push_back(std::move(row));
  }
  
  return rows;
}