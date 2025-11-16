#include "diamond.h"

#include <algorithm>
#include <string>
#include <vector>

namespace diamond {

std::vector<std::string> rows(char ch) {
  if (ch == 'A') {
    return {"A"};
  }

  int num_spaces = ch - 'A';
  int num_lines = (num_spaces * 2) + 1;
  std::vector<std::string> out(num_lines, std::string(num_lines, ' '));

  int mid = num_lines / 2;

  for (int i = 0; i <= mid; ++i) {
    char current_char = 'A' + i;
    if (i == 0) {
      out[mid][mid] = current_char;
    } else {
      out[i][mid - i] = current_char;
      out[i][mid + i] = current_char;
      out[num_lines - 1 - i][mid - i] = current_char;
      out[num_lines - 1 - i][mid + i] = current_char;
    }
  }

  for (auto& row : out) {
    // No need to copy, modify in place
  }

  return out;
}

}  // namespace diamond