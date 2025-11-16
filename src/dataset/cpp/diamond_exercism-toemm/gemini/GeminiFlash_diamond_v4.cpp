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

  for (int i = 0; i <= num_spaces; ++i) {
    char currentChar = 'A' + i;
    int outerSpaces = num_spaces - i;
    int innerSpaces = (i == 0) ? 0 : num_lines - 2 - 2 * outerSpaces;

    out[i][outerSpaces] = currentChar;
    out[num_lines - 1 - i][outerSpaces] = currentChar;

    if (currentChar != 'A') {
      out[i][num_lines - 1 - outerSpaces] = currentChar;
      out[num_lines - 1 - i][num_lines - 1 - outerSpaces] = currentChar;
    }
  }

  return out;
}

}  // namespace diamond