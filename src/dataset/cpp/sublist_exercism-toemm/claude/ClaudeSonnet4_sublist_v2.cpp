#include "sublist.h"

#include <cassert>
#include <algorithm>

namespace sublist {

List_comparison sublist(const std::vector<int>& a, const std::vector<int>& b) {
    const auto size_a = a.size();
    const auto size_b = b.size();

    if (size_a == size_b) {
        return (a == b) ? List_comparison::equal : List_comparison::unequal;
    }

    // check b contains a
    if (size_a < size_b) {
        if (size_a == 0) return List_comparison::sublist;
        
        return std::search(b.begin(), b.end(), a.begin(), a.end()) != b.end() 
            ? List_comparison::sublist 
            : List_comparison::unequal;
    }
    
    // check if a contains b
    if (size_b == 0) return List_comparison::superlist;
    
    return std::search(a.begin(), a.end(), b.begin(), b.end()) != a.end() 
        ? List_comparison::superlist 
        : List_comparison::unequal;
}

}  // namespace sublist