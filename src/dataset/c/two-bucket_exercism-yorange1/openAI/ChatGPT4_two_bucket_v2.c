#include "two_bucket.h"

#include <stdint.h>
#include <stdio.h>

#define is_even(x) ((x & 1) == 0)
#define BUCKET_NUM (2)

static bucket_liters_t bucket_size[BUCKET_NUM] = {0};
static bucket_liters_t bucket_state[BUCKET_NUM] = {0};

static uint32_t gcd(uint32_t a, uint32_t b)
{
    while (b != 0)
    {
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
    return (goal_volume % gcd(bucket_1_size, bucket_2_size) == 0 &&
            goal_volume <= (bucket_1_size > bucket_2_size ? bucket_1_size : bucket_2_size));
}

static inline bool is_full(bucket_id_t bucket_id)
{
    return bucket_state[bucket_id] == bucket_size[bucket_id];
}

static inline bool is_empty(bucket_id_t bucket_id)
{
    return bucket_state[bucket_id] == 0;
}

static inline bool is_reach(bucket_liters_t goal_volume)
{
    return bucket_state[BUCKET_ID_1] == goal_volume || bucket_state[BUCKET_ID_2] == goal_volume;
}

static inline void empty(bucket_id_t bucket_id)
{
    bucket_state[bucket_id] = 0;
}

static inline void fill(bucket_id_t bucket_id)
{
    bucket_state[bucket_id] = bucket_size[bucket_id];
}

static inline void pour(bucket_id_t from, bucket_id_t to)
{
    bucket_liters_t transfer = bucket_size[to] - bucket_state[to];
    if (bucket_state[from] <= transfer)
    {
        bucket_state[to] += bucket_state[from];
        bucket_state[from] = 0;
    }
    else
    {
        bucket_state[to] = bucket_size[to];
        bucket_state[from] -= transfer;
    }
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
        result.move_count = start_bucket == BUCKET_ID_1 ? 1 : 2;
        result.other_bucket_liters = start_bucket == BUCKET_ID_1 ? 0 : bucket_2_size;
        return result;
    }

    if (bucket_2_size == goal_volume)
    {
        result.goal_bucket = BUCKET_ID_2;
        result.move_count = start_bucket == BUCKET_ID_2 ? 1 : 2;
        result.other_bucket_liters = start_bucket == BUCKET_ID_2 ? 0 : bucket_1_size;
        return result;
    }

    bucket_size[BUCKET_ID_1] = bucket_1_size;
    bucket_size[BUCKET_ID_2] = bucket_2_size;
    bucket_state[BUCKET_ID_1] = 0;
    bucket_state[BUCKET_ID_2] = 0;

    fill(start_bucket);
    result.move_count++;

    bucket_id_t non_start_bucket = (bucket_id_t)!start_bucket;

    while (!is_reach(goal_volume))
    {
        if (is_empty(start_bucket))
        {
            fill(start_bucket);
        }
        else if (!is_full(non_start_bucket))
        {
            pour(start_bucket, non_start_bucket);
        }
        else
        {
            empty(non_start_bucket);
        }

        result.move_count++;
    }

    result.goal_bucket = bucket_state[start_bucket] == goal_volume ? start_bucket : non_start_bucket;
    result.other_bucket_liters = bucket_state[!result.goal_bucket];

    return result;
}