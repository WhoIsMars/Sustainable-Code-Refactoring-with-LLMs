#pragma once

#include <vector>

namespace sublist {

enum class List_comparison {        
    equal, sublist, superlist, unequal
};



List_comparison sublist(std::vector<int> a, std::vector<int> b);

}  // namespace sublist
