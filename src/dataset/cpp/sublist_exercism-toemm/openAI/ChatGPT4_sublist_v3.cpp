#include "sublist.h"

#include <vector>

namespace sublist {

List_comparison sublist(const std::vector<int>& a, const std::vector<int>& b) {
    auto size_a = a.size();
    auto size_b = b.size();

    if (a == b) return List_comparison::equal;

    if (size_a < size_b) {
        if (a.empty()) return List_comparison::sublist;

        for (std::size_t i = 0; i <= size_b - size_a; ++i) {
            if (std::equal(a.begin(), a.end(), b.begin() + i)) {
                return List_comparison::sublist;
            }
        }
    } else if (size_a > size_b) {
        if (b.empty()) return List_comparison::superlist;

        for (std::size_t i = 0; i <= size_a - size_b; ++i) {
            if (std::equal(b.begin(), b.end(), a.begin() + i)) {
                return List_comparison::superlist;
            }
        }
    }

    return List_comparison::unequal;
}

}  // namespace sublist