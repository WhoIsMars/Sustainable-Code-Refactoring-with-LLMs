#include "pythagorean_triplet.h"

#include <stdlib.h>
#include <string.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

triplets_t *triplets_with_sum(uint16_t sum)
{
    uint16_t count = 0;

    // Allocate memory for the triplets dynamically as we find them
    triplets_t *triplets = (triplets_t *)calloc(1, sizeof(triplets_t));
    if (NULL == triplets)
    {
        return NULL;
    }

    for (uint16_t a = 1; a <= sum / 3; a++)
    {
        for (uint16_t b = a + 1; b <= (sum - a) / 2; b++)
        {
            uint16_t c = sum - a - b;

            if (a * a + b * b == c * c)
            {
                triplet_t *new_triplets = realloc(triplets->triplets, (count + 1) * sizeof(triplet_t));
                if (NULL == new_triplets)
                {
                    free(triplets->triplets);
                    free(triplets);
                    return NULL;
                }

                triplets->triplets = new_triplets;
                triplets->triplets[count].a = a;
                triplets->triplets[count].b = b;
                triplets->triplets[count].c = c;
                count++;
            }
        }
    }

    triplets->count = count;

    return triplets;
}

void free_triplets(triplets_t *triplets)
{
    if (triplets)
    {
        free(triplets->triplets);
        free(triplets);
    }
}