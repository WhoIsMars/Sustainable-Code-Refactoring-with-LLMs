#include "pythagorean_triplet.h"

#include <stdlib.h>
#include <math.h>

triplets_t *triplets_with_sum(uint16_t sum) {
    uint16_t max_a = sum / 3;
    uint16_t count = 0;
    triplet_t *temp = NULL;
    triplets_t *triplets = NULL;

    // Initial allocation, assuming a reasonable number of triplets
    size_t initial_capacity = 4;
    temp = (triplet_t *)malloc(initial_capacity * sizeof(triplet_t));
    if (temp == NULL) return NULL;

    size_t capacity = initial_capacity;

    for (uint16_t a = 1; a <= max_a; ++a) {
        uint16_t max_b = (sum - a) / 2;
        for (uint16_t b = a + 1; b <= max_b; ++b) {
            uint16_t c = sum - a - b;
            if (a * a + b * b == c * c) {
                // Resize temp array if needed
                if (count == capacity) {
                    capacity *= 2;
                    triplet_t *new_temp = (triplet_t *)realloc(temp, capacity * sizeof(triplet_t));
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

    // Copy the triplets to the triplets array
    for (size_t i = 0; i < count; ++i) {
        triplets->triplets[i].a = temp[i].a;
        triplets->triplets[i].b = temp[i].b;
        triplets->triplets[i].c = temp[i].c;
    }

    triplets->count = count;

    free(temp); // Free the temporary array

    return triplets;
}


void free_triplets(triplets_t *triplets) {
    if (triplets) {
        free(triplets->triplets);
        free(triplets);
    }
}