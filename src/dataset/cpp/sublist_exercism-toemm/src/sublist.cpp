#include "sublist.h"

#include <cassert>

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

    auto size_a = a.size();
    auto size_b = b.size();

    if (a == b) return List_comparison::equal;

    // check b contains a
    if (size_a < size_b) {

        if (a.empty()) return List_comparison::sublist;

        for (std::size_t i{}; i <= size_b - size_a; i++) {
            auto window = std::vector<int>(b.begin() + i, b.begin() + i + size_a);

            assert(window.size() == a.size());

            if (window == a) return List_comparison::sublist;
        }

    // check if a contains b
    } else if (size_a > size_b) {

        if (b.empty()) return List_comparison::superlist;

        for (std::size_t i{}; i <= size_a - size_b; i++) {
            auto window = std::vector<int>(a.begin() + i, a.begin() + i + size_b);

            assert(window.size() == b.size());

            if (window == b) return List_comparison::superlist;
        }
    } 

    return List_comparison::unequal;

}

}  // namespace sublist
