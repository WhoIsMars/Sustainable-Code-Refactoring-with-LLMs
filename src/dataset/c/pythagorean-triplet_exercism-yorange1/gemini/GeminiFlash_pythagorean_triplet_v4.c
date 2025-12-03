#include "pythagorean_triplet.h"

#include <stdlib.h>
#include <math.h>

triplets_t *triplets_with_sum(uint16_t sum)
{
    uint16_t max_a = sum / 3;
    uint16_t count = 0;
    triplet_t *temp = NULL;
    triplets_t *triplets = NULL;

    // Initial allocation for a small number of triplets.  Reallocate if needed.
    size_t temp_size = 4;
    temp = (triplet_t *)malloc(temp_size * sizeof(triplet_t));
    if (temp == NULL)
    {
        return NULL;
    }

    for (uint16_t a = 1; a <= max_a; a++)
    {
        uint16_t b = (sum * sum - 2 * sum * a) / (2 * (sum - a));

        if (b <= a) continue;

        uint16_t c = sum - a - b;

        if (a * a + b * b == c * c && a < b && b < c)
        {
            if (count == temp_size)
            {
                temp_size *= 2;
                triplet_t *new_temp = (triplet_t *)realloc(temp, temp_size * sizeof(triplet_t));
                if (new_temp == NULL)
                {
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

    triplets = (triplets_t *)malloc(sizeof(triplets_t));
    if (NULL == triplets)
    {
        free(temp);
        return NULL;
    }

    triplets->triplets = (triplet_t *)malloc(count * sizeof(triplet_t));
    if (triplets->triplets == NULL)
    {
        free(temp);
        free(triplets);
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        triplets->triplets[i].a = temp[i].a;
        triplets->triplets[i].b = temp[i].b;
        triplets->triplets[i].c = temp[i].c;
    }

    free(temp);

    triplets->count = count;

    return triplets;
}

void free_triplets(triplets_t *triplets)
{
    if (triplets) {
        free(triplets->triplets);
        free(triplets);
    }
}