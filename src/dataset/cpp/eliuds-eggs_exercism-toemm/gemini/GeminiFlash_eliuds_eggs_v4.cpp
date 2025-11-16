#include "eliuds_eggs.h"

namespace chicken_coop {

int positions_to_quantity(int i) {
    int count = 0;
    while (i > 0) {
        count += (i & 1);
        i >>= 1;
    }
    return count;
}

}  // namespace chicken_coop