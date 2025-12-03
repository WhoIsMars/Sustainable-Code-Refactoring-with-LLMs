#include "two_bucket.h"

#include <stdint.h>
#include <stdio.h>

#define BUCKET_NUM (2)

static bucket_liters_t bucket_size[BUCKET_NUM];
static bucket_liters_t bucket_state[BUCKET_NUM];

static uint32_t gcd(uint32_t a, uint32_t b)
{
    while (b != 0) {
        uint32_t temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

static bool is_possible(bucket_liters_t bucket_1_size,
                        bucket_liters_t bucket_2_size,
                        bucket_liters_t goal_volume)
{
    uint32_t g = gcd(bucket_1_size, bucket_2_size);
    return (goal_volume % g == 0 &&
            (goal_volume <= bucket_1_size || goal_volume <= bucket_2_size));
}

static void empty(bucket_id_t bucket_id)
{
    bucket_state[bucket_id] = 0;
    printf("emptying bucket %d\n", bucket_id);
}

static void fill(bucket_id_t bucket_id)
{
    bucket_state[bucket_id] = bucket_size[bucket_id];
    printf("filling bucket %d\n", bucket_id);
}

static void pour(bucket_id_t from, bucket_id_t to)
{
    bucket_liters_t available_space = bucket_size[to] - bucket_state[to];
    bucket_liters_t pour_amount = (bucket_state[from] <= available_space) ? 
                                  bucket_state[from] : available_space;
    
    bucket_state[to] += pour_amount;
    bucket_state[from] -= pour_amount;

    printf("pouring form bucket %d to %d\n", from, to);
}

static void print_bucket()
{
    printf("bucket state (%d, %d)\n", bucket_state[BUCKET_ID_1], bucket_state[BUCKET_ID_2]);
}

bucket_result_t measure(bucket_liters_t bucket_1_size,
                        bucket_liters_t bucket_2_size,
                        bucket_liters_t goal_volume, bucket_id_t start_bucket)
{
    bucket_result_t result = {0};

    if (!(result.possible = is_possible(bucket_1_size, bucket_2_size, goal_volume)))
    {
        return result;
    }

    if (bucket_1_size == goal_volume)
    {
        result.goal_bucket = BUCKET_ID_1;
        result.move_count = (start_bucket == BUCKET_ID_1) ? 1 : 2;
        result.other_bucket_liters = (start_bucket == BUCKET_ID_1) ? 0 : bucket_2_size;
        return result;
    }
    
    if (bucket_2_size == goal_volume)
    {
        result.goal_bucket = BUCKET_ID_2;
        result.move_count = (start_bucket == BUCKET_ID_2) ? 1 : 2;
        result.other_bucket_liters = (start_bucket == BUCKET_ID_2) ? 0 : bucket_1_size;
        return result;
    }

    bucket_size[BUCKET_ID_1] = bucket_1_size;
    bucket_size[BUCKET_ID_2] = bucket_2_size;
    bucket_state[BUCKET_ID_1] = 0;
    bucket_state[BUCKET_ID_2] = 0;

    fill(start_bucket);
    result.move_count = 1;
    print_bucket();

    bucket_id_t non_start_bucket = 1 - start_bucket;

    while (bucket_state[BUCKET_ID_1] != goal_volume && bucket_state[BUCKET_ID_2] != goal_volume)
    {
        if (bucket_state[start_bucket] == 0)
        {
            fill(start_bucket);
        }
        else if (bucket_state[non_start_bucket] < bucket_size[non_start_bucket])
        {
            pour(start_bucket, non_start_bucket);
        }
        else
        {
            empty(non_start_bucket);
        }

        print_bucket();
        result.move_count++;
    }

    result.goal_bucket = (bucket_state[start_bucket] == goal_volume) ? start_bucket : non_start_bucket;
    result.other_bucket_liters = bucket_state[1 - result.goal_bucket];

    return result;
}