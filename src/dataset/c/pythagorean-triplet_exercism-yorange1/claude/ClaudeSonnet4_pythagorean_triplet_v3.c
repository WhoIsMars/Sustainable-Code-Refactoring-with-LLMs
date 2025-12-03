#include "pythagorean_triplet.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

triplets_t *triplets_with_sum(uint16_t sum)
{
    if (sum < 12) {
        triplets_t *triplets = (triplets_t *)calloc(1, sizeof(triplets_t));
        if (triplets) {
            triplets->count = 0;
        }
        return triplets;
    }

    triplet_t *temp = (triplet_t *)malloc(sum * sizeof(triplet_t));
    if (!temp) {
        return NULL;
    }
    
    uint16_t count = 0;
    uint16_t sum_half = sum / 2;

    for (uint16_t a = 1; a < sum_half; a++)
    {
        uint16_t max_b = (sum - a) / 2;
        if (max_b <= a) break;
        
        for (uint16_t b = a + 1; b <= max_b; b++)
        {
            uint16_t c = sum - a - b;
            
            if (c <= b) break;
            
            if (a * a + b * b == c * c)
            {
                temp[count].a = a;
                temp[count].b = b;
                temp[count].c = c;
                count++;
            }
        }
    }

    triplets_t *triplets = (triplets_t *)malloc(sizeof(triplets_t) + count * sizeof(triplet_t));
    if (!triplets)
    {
        free(temp);
        return NULL;
    }

    if (count > 0) {
        memcpy(triplets->triplets, temp, count * sizeof(triplet_t));
    }
    triplets->count = count;
    
    free(temp);
    return triplets;
}

void free_triplets(triplets_t *triplets)
{
    free(triplets);
}