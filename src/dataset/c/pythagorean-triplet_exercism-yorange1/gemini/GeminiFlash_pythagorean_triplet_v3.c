#include "pythagorean_triplet.h"

#include <stdlib.h>
#include <math.h>

triplets_t *triplets_with_sum(uint16_t sum) {
    uint16_t max_a = sum / 3;
    uint16_t count = 0;
    triplet_t *temp = NULL;
    triplets_t *triplets = NULL;

    // Estimate the maximum possible number of triplets to avoid reallocations
    size_t estimated_max_triplets = max_a;
    temp = (triplet_t *)malloc(estimated_max_triplets * sizeof(triplet_t));
    if (temp == NULL) {
        return NULL;
    }

    for (uint16_t a = 1; a <= max_a; ++a) {
        uint16_t max_b = (sum - a) / 2;
        for (uint16_t b = a + 1; b <= max_b; ++b) {
            uint16_t c = sum - a - b;
            if (a * a + b * b == c * c) {
                // Check if we need to reallocate
                if (count >= estimated_max_triplets) {
                    estimated_max_triplets *= 2;
                    triplet_t *new_temp = (triplet_t *)realloc(temp, estimated_max_triplets * sizeof(triplet_t));
                    if (new_temp == NULL) {
                        free(temp);
                        return NULL;
                    }
                    temp = new_temp;
                }
                temp[count].a = a;
                temp[count].b = b;
                temp[count].c = c;
                count++;
            }
        }
    }

    triplets = (triplets_t *)malloc(sizeof(triplets_t));
    if (triplets == NULL) {
        free(temp);
        return NULL;
    }

    triplets->triplets = (triplet_t *)malloc(count * sizeof(triplet_t));
    if (triplets->triplets == NULL) {
        free(temp);
        free(triplets);
        return NULL;
    }

    memcpy(triplets->triplets, temp, count * sizeof(triplet_t));
    triplets->count = count;

    free(temp);
    return triplets;
}

void free_triplets(triplets_t *triplets) {
    if (triplets) {
        free(triplets->triplets);
        free(triplets);
    }
}