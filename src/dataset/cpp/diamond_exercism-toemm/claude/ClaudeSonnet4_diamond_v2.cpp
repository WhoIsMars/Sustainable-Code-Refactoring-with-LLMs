#include "diamond.h"

namespace diamond {

    std::vector<std::string> rows(char ch) {
        if (ch == 'A') return {"A"};
    
        int num_spaces = ch - 'A';
        int num_lines = (num_spaces * 2) + 1;
        int line_width = num_lines;
        
        std::vector<std::string> out;
        out.reserve(num_lines);
        
        for (int i = 0; i <= num_spaces; ++i) {
            std::string line;
            line.reserve(line_width);
            
            // Add leading spaces
            line.append(num_spaces - i, ' ');
            
            // Add first character
            line.push_back('A' + i);
            
            if (i == 0) {
                // For 'A', just add trailing spaces
                line.append(num_spaces, ' ');
            } else {
                // Add middle spaces and second character
                line.append(2 * i - 1, ' ');
                line.push_back('A' + i);
                line.append(num_spaces - i, ' ');
            }
            
            out.push_back(line);
        }
        
        // Mirror the upper half (excluding middle line)
        for (int i = num_spaces - 1; i >= 0; --i) {
            out.push_back(out[i]);
        }
        
        return out;
    }

}  // namespace diamond