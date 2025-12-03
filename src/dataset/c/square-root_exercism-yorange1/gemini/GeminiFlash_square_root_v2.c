#include "square_root.h"

#include <stdint.h>

uint16_t square_root(uint16_t number) {
    if (number == 0) {
        return 0;
    }

    uint16_t root = number;
    uint16_t next_root;

    while (true) {
        next_root = (root + number / root) / 2;
        if (next_root >= root) {
            return root;
        }
        root = next_root;
    }
}