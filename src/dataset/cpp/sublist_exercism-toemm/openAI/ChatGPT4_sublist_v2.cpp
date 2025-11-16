#include "sublist.h"

#include <vector>

namespace sublist {

/**
 * Vergleicht zwei Listen und bestimmt ihre Beziehung zueinander.
 * @param a Erste Liste
 * @param b Zweite Liste
 * @return List_comparison::equal wenn die Listen identisch sind,
 *         List_comparison::sublist wenn a eine Sublist von b ist,
 *         List_comparison::superlist wenn a eine Superlist von b ist,
 *         List_comparison::unequal wenn keine der obigen Beziehungen zutrifft
 */

List_comparison sublist(const std::vector<int>& a, const std::vector<int>& b) {
    auto size_a = a.size();
    auto size_b = b.size();

    if (a == b) return List_comparison::equal;

    // Helper lambda to check if one vector is a sublist of another
    auto is_sublist = [](const std::vector<int>& smaller, const std::vector<int>& larger) {
        auto size_smaller = smaller.size();
        auto size_larger = larger.size();
        for (std::size_t i = 0; i <= size_larger - size_smaller; ++i) {
            if (std::equal(smaller.begin(), smaller.end(), larger.begin() + i)) {
                return true;
            }
        }
        return false;
    };

    if (size_a < size_b) {
        if (a.empty() || is_sublist(a, b)) return List_comparison::sublist;
    } else if (size_a > size_b) {
        if (b.empty() || is_sublist(b, a)) return List_comparison::superlist;
    }

    return List_comparison::unequal;
}

}  // namespace sublist