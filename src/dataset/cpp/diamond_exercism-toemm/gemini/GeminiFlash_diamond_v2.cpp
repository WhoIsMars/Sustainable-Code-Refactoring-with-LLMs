#include "diamond.h"

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

  for (int i = 0; i <= num_spaces; ++i) {
    char current_char = 'A' + i;
    int outer_spaces = num_spaces - i;
    int inner_spaces = (i == 0) ? 0 : (num_lines - 2 * (outer_spaces + 1));

    out[i][outer_spaces] = current_char;
    out[num_lines - 1 - i][outer_spaces] = current_char;

    if (current_char != 'A') {
      out[i][num_lines - 1 - outer_spaces] = current_char;
      out[num_lines - 1 - i][num_lines - 1 - outer_spaces] = current_char;
    }
  }

  return out;
}

}  // namespace diamond