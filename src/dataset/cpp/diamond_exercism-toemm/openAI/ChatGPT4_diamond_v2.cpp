#include "diamond.h"

#include <vector>
#include <string>

namespace diamond {

    std::vector<std::string> rows(char ch) {
        if (ch == 'A') return {"A"};

        int num_spaces = ch - 'A';
        int num_lines = (num_spaces * 2) + 1;
        std::vector<std::string> out(num_lines);

        for (int i = 0; i <= num_spaces; ++i) {
            char current_char = 'A' + i;
            int outer_spaces = num_spaces - i;
            int inner_spaces = (i == 0) ? 0 : (2 * i - 1);

            std::string line(outer_spaces, ' ');
            line += current_char;
            if (inner_spaces > 0) {
                line += std::string(inner_spaces, ' ') + current_char;
            }
            line += std::string(outer_spaces, ' ');

            out[i] = line;
            out[num_lines - i - 1] = line;
        }

        return out;
    }

}  // namespace diamond