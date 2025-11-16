#include "sublist.h"

#include <algorithm>

namespace sublist {

List_comparison sublist(std::vector<int> a, std::vector<int> b) {
    auto size_a = a.size();
    auto size_b = b.size();

    if (size_a == size_b) {
        if (a == b) return List_comparison::equal;
    } else if (size_a < size_b) {
        if (size_a == 0) return List_comparison::sublist;
        for (std::size_t i = 0; i <= size_b - size_a; ++i) {
            if (std::equal(a.begin(), a.end(), b.begin() + i)) {
                return List_comparison::sublist;
            }
        }
    } else {
        if (size_b == 0) return List_comparison::superlist;
        for (std::size_t i = 0; i <= size_a - size_b; ++i) {
            if (std::equal(b.begin(), b.end(), a.begin() + i)) {
                return List_comparison::superlist;
            }
        }
    }

    return List_comparison::unequal;
}

}  // namespace sublist