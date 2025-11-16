#include "minesweeper.h"

namespace minesweeper {

std::vector<std::string> annotate(std::vector<std::string> input) noexcept {

    if (input.empty()) return input;
    
    // generate padded vector so dont have to check boundaries
    auto padded = input;

    for (auto& line : padded) {
        line.insert(0, "X");
        line.push_back('X');
    }

    padded.insert(padded.begin(), std::string(padded[0].size(), 'X'));
    padded.push_back(std::string(padded[0].size(), 'X'));


    for (std::size_t i{}; i < padded.size(); i++) {
        
        for (std::size_t j{}; j < padded[0].size(); j++) {

            auto elem = padded[i][j];
            int ctr{};

            if (elem == '*' || elem == 'X') continue;

            // found non mine element
            else {
                // up row
                auto up_row = padded[i-1];

                if (up_row[j-1] == '*') ctr++;
                if (up_row[j] == '*') ctr++;
                if (up_row[j+1] == '*') ctr++;

                // same row
                if (padded[i][j-1] == '*') ctr++;
                if (padded[i][j+1] == '*') ctr++;

                // down row
                auto down_row = padded[i+1];

                if (down_row[j-1] == '*') ctr++;
                if (down_row[j] == '*') ctr++;
                if (down_row[j+1] == '*') ctr++;

                // annotation
                if (ctr > 0) {
                    
                    input[i-1][j-1] = '0' + ctr;

                }
            }


        }



    }

    return input;


}

}  // namespace minesweeper
