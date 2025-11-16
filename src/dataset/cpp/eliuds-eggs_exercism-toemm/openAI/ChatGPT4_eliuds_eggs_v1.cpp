#include "eliuds_eggs.h"

namespace chicken_coop {

int positions_to_quantity(int i) {
    int ctr = 0;
    while (i) {
        ctr += (i & 1);
        i >>= 1;
    }
    return ctr;
}

}  // namespace chicken_coop