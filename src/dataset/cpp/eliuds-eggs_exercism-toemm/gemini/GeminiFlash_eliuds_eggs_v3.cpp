#include "eliuds_eggs.h"

namespace chicken_coop {

int positions_to_quantity(int i) {
    int count = 0;
    while (i) {
        i &= (i - 1);
        count++;
    }
    return count;
}

}  // namespace chicken_coop