#include "sublist.h"

#include <cassert>
#include <algorithm>

namespace sublist {

List_comparison sublist(std::vector<int> a, std::vector<int> b) {
    const auto size_a = a.size();
    const auto size_b = b.size();

    if (size_a == size_b) {
        return (a == b) ? List_comparison::equal : List_comparison::unequal;
    }

    if (size_a < size_b) {
        if (size_a == 0) return List_comparison::sublist;
        
        auto it = std::search(b.begin(), b.end(), a.begin(), a.end());
        return (it != b.end()) ? List_comparison::sublist : List_comparison::unequal;
    } else {
        if (size_b == 0) return List_comparison::superlist;
        
        auto it = std::search(a.begin(), a.end(), b.begin(), b.end());
        return (it != a.end()) ? List_comparison::superlist : List_comparison::unequal;
    }
}

}  // namespace sublist