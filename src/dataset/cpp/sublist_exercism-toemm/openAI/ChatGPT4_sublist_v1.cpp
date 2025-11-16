#include "sublist.h"

#include <cassert>
#include <algorithm>

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

    // Lambda to check if smaller is a sublist of larger
    auto is_sublist = [](const std::vector<int>& smaller, const std::vector<int>& larger) {
        return std::search(larger.begin(), larger.end(), smaller.begin(), smaller.end()) != larger.end();
    };

    if (size_a < size_b) {
        return a.empty() || is_sublist(a, b) ? List_comparison::sublist : List_comparison::unequal;
    } else if (size_a > size_b) {
        return b.empty() || is_sublist(b, a) ? List_comparison::superlist : List_comparison::unequal;
    }

    return List_comparison::unequal;
}

}  // namespace sublist