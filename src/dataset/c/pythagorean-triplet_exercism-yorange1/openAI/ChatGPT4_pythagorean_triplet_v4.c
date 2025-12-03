#include "pythagorean_triplet.h"

#include <stdlib.h>
#include <string.h>

triplets_t *triplets_with_sum(uint16_t sum)
{
    uint16_t count = 0;
    triplet_t *temp = (triplet_t *)malloc((sum / 2) * sizeof(triplet_t));
    if (temp == NULL)
    {
        return NULL;
    }

    for (uint16_t a = 1; a < sum / 3; a++)
    {
        for (uint16_t b = a + 1; b < (sum - a) / 2; b++)
        {
            uint16_t c = sum - a - b;

            if (a * a + b * b == c * c)
            {
                temp[count++] = (triplet_t){.a = a, .b = b, .c = c};
            }
        }
    }

    triplets_t *triplets = (triplets_t *)malloc(sizeof(triplets_t) + count * sizeof(triplet_t));
    if (triplets == NULL)
    {
        free(temp);
        return NULL;
    }

    memcpy(triplets->triplets, temp, count * sizeof(triplet_t));
    triplets->count = count;

    free(temp);
    return triplets;
}

void free_triplets(triplets_t *triplets)
{
    free(triplets);
}