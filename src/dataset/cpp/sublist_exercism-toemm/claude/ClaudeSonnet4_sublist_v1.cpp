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

List_comparison sublist(std::vector<int> a, std::vector<int> b) {
    const auto size_a = a.size();
    const auto size_b = b.size();

    if (size_a == size_b) {
        return (a == b) ? List_comparison::equal : List_comparison::unequal;
    }

    // check b contains a
    if (size_a < size_b) {
        if (size_a == 0) return List_comparison::sublist;

        auto it = std::search(b.begin(), b.end(), a.begin(), a.end());
        return (it != b.end()) ? List_comparison::sublist : List_comparison::unequal;

    // check if a contains b
    } else {
        if (size_b == 0) return List_comparison::superlist;

        auto it = std::search(a.begin(), a.end(), b.begin(), b.end());
        return (it != a.end()) ? List_comparison::superlist : List_comparison::unequal;
    }
}

}  // namespace sublist