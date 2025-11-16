#include "diamond.h"

#include <algorithm>

namespace diamond {

    std::vector<std::string> rows(char ch) {


        if (ch == 'A') return {"A"};
    
        int num_spaces = ch - 'A';
        int num_lines = (num_spaces * 2) + 1;
        std::vector<std::string> out{static_cast<std::size_t>(num_lines)};
    
        int ch_start = 'A';
    
        for (int i{}; num_spaces >= 0; num_spaces--, i++) {
    
            std::string beg{};
            std::string line{};
    
            beg.append(num_spaces, ' ');
            beg.push_back(ch_start);
            line.append(beg);
    
            if (ch_start == 'A') {
                line.append(num_spaces, ' ');
            } else {
                line.append(num_lines - 2 * beg.size(), ' ');
                std::reverse(beg.begin(), beg.end());
                line.append(beg);
            }
    
            ch_start++;
    
            *(out.begin() + i) = line;
    
            if (num_spaces != 0) {
                *(out.end() - i - 1) = line;
            }
            
        }
    
    
        return out;
    
    
    
    }

}  // namespace diamond
