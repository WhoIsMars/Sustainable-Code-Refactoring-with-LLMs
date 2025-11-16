#include "diamond.h"

namespace diamond {

    std::vector<std::string> rows(char ch) {
        if (ch == 'A') return {"A"};
        
        const int size = ch - 'A';
        const int num_lines = (size * 2) + 1;
        const int line_width = num_lines;
        
        std::vector<std::string> result;
        result.reserve(num_lines);
        
        for (int i = 0; i <= size; ++i) {
            const int spaces_before = size - i;
            const char current_char = 'A' + i;
            
            std::string line;
            line.reserve(line_width);
            
            line.append(spaces_before, ' ');
            line.push_back(current_char);
            
            if (i == 0) {
                line.append(spaces_before, ' ');
            } else {
                const int spaces_middle = 2 * i - 1;
                line.append(spaces_middle, ' ');
                line.push_back(current_char);
                line.append(spaces_before, ' ');
            }
            
            result.push_back(line);
        }
        
        for (int i = size - 1; i >= 0; --i) {
            result.push_back(result[i]);
        }
        
        return result;
    }

}  // namespace diamond