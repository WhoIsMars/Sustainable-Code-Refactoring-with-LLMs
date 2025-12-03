#include "two_bucket.h"

#include <stdint.h>
#include <stdbool.h>

#define BUCKET_NUM (2)

typedef uint32_t bucket_liters_t;
typedef uint8_t bucket_id_t;

static inline uint32_t gcd(uint32_t a, uint32_t b) {
    while (b != 0) {
        uint32_t temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

static inline bool is_possible(bucket_liters_t bucket_1_size,
                               bucket_liters_t bucket_2_size,
                               bucket_liters_t goal_volume) {
    return (goal_volume % gcd(bucket_1_size, bucket_2_size) == 0 &&
            (goal_volume <= bucket_1_size || goal_volume <= bucket_2_size));
}

bucket_result_t measure(bucket_liters_t bucket_1_size,
                        bucket_liters_t bucket_2_size,
                        bucket_liters_t goal_volume, bucket_id_t start_bucket) {
    bucket_result_t result = {0};

    if (!is_possible(bucket_1_size, bucket_2_size, goal_volume)) {
        return result;
    }

    if (bucket_1_size == goal_volume) {
        result.possible = true;
        result.goal_bucket = BUCKET_ID_1;
        result.move_count = start_bucket == BUCKET_ID_1 ? 1 : 2;
        result.other_bucket_liters = start_bucket == BUCKET_ID_1 ? 0 : bucket_2_size;
        return result;
    }

    if (bucket_2_size == goal_volume) {
        result.possible = true;
        result.goal_bucket = BUCKET_ID_2;
        result.move_count = start_bucket == BUCKET_ID_2 ? 1 : 2;
        result.other_bucket_liters = start_bucket == BUCKET_ID_2 ? 0 : bucket_1_size;
        return result;
    }

    bucket_liters_t bucket_state[BUCKET_NUM] = {0};
    bucket_liters_t bucket_size[BUCKET_NUM] = {bucket_1_size, bucket_2_size};

    bucket_id_t other_bucket = (bucket_id_t)!start_bucket;
    bucket_state[start_bucket] = bucket_size[start_bucket];
    result.move_count = 1;

    while (bucket_state[start_bucket] != goal_volume && bucket_state[other_bucket] != goal_volume) {
        if (bucket_state[other_bucket] == bucket_size[other_bucket]) {
            bucket_state[other_bucket] = 0;
            result.move_count++;
        } else if (bucket_state[start_bucket] == 0) {
            bucket_state[start_bucket] = bucket_size[start_bucket];
            result.move_count++;
        } else {
            bucket_liters_t pour_amount = (bucket_size[other_bucket] - bucket_state[other_bucket] < bucket_state[start_bucket]) ? (bucket_size[other_bucket] - bucket_state[other_bucket]) : bucket_state[start_bucket];
            bucket_state[start_bucket] -= pour_amount;
            bucket_state[other_bucket] += pour_amount;
            result.move_count++;
        }
    }

    result.possible = true;
    result.goal_bucket = (bucket_state[BUCKET_ID_1] == goal_volume) ? BUCKET_ID_1 : BUCKET_ID_2;
    result.other_bucket_liters = bucket_state[(bucket_id_t)!result.goal_bucket];

    return result;
}