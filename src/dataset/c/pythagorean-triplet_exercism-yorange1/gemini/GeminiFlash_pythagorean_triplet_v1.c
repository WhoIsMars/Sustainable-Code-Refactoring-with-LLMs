#include "pythagorean_triplet.h"

#include <stdlib.h>
#include <math.h>

triplets_t *triplets_with_sum(uint16_t sum) {
    uint16_t max_a = sum / 3;
    size_t max_triplets = max_a * max_a;
    triplet_t *temp = (triplet_t *)malloc(max_triplets * sizeof(triplet_t));

    if (!temp) return NULL;

    uint16_t count = 0;

    for (uint16_t a = 1; a <= max_a; ++a) {
        uint16_t b = (sum * sum - 2 * sum * a) / (2 * (sum - a));

        if (b <= a) continue;

        uint16_t c = sum - a - b;

        if (a * a + b * b == c * c && b < c) {
            temp[count].a = a;
            temp[count].b = b;
            temp[count].c = c;
            count++;
        }
    }

    triplets_t *triplets = (triplets_t *)malloc(sizeof(triplets_t));
    if (NULL == triplets) {
        free(temp);
        return NULL;
    }

    triplets->triplets = (triplet_t *)malloc(count * sizeof(triplet_t));
    if (NULL == triplets->triplets) {
        free(temp);
        free(triplets);
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        triplets->triplets[i] = temp[i];
    }

    free(temp);
    triplets->count = count;

    return triplets;
}

void free_triplets(triplets_t *triplets) {
    if (triplets) {
        free(triplets->triplets);
        free(triplets);
    }
}