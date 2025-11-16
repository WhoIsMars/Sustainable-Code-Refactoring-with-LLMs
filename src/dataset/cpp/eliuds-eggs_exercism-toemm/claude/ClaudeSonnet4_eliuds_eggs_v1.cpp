#include "eliuds_eggs.h"

namespace chicken_coop {

int positions_to_quantity(int i) {
    return __builtin_popcount(i);
}

}  // namespace chicken_coop