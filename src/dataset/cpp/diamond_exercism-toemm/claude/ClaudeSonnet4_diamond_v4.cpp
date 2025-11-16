#include "diamond.h"

namespace diamond {

    std::vector<std::string> rows(char ch) {
        if (ch == 'A') return {"A"};
        
        const int num_chars = ch - 'A' + 1;
        const int num_lines = (num_chars - 1) * 2 + 1;
        const int width = num_lines;
        
        std::vector<std::string> out;
        out.reserve(num_lines);
        
        for (int i = 0; i < num_chars; ++i) {
            std::string line(width, ' ');
            const char current_char = 'A' + i;
            const int outer_spaces = num_chars - 1 - i;
            
            line[outer_spaces] = current_char;
            if (i > 0) {
                line[width - 1 - outer_spaces] = current_char;
            }
            
            out.push_back(line);
            if (i > 0) {
                out.insert(out.end() - 1, line);
            }
        }
        
        return out;
    }

}