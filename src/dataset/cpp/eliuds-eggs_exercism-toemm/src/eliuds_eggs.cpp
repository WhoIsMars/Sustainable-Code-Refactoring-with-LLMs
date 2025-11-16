#include "eliuds_eggs.h"

namespace chicken_coop {

int positions_to_quantity(int i) {

    int ctr{};


    for (; i > 0; i /= 2) {

        if (i % 2 != 0) ctr++;

    }


    return ctr;



}

}  // namespace chicken_coop
