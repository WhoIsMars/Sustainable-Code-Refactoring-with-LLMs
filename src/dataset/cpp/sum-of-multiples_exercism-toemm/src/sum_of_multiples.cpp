#include "sum_of_multiples.h"

#include <vector>
#include <iostream>

namespace sum_of_multiples {


int to(const std::vector<int>& bases, const int level) {

    int out{};

    for (int i{}; i < level; i++) {
        for (auto num : bases) {
            if (i % num == 0) {
                out += i;
                break;
            }
        }
    }
    


    return out;


}

}  // namespace sum_of_multiples
