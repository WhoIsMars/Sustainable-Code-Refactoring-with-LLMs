#include "two_bucket.h"

#include <stdint.h>
#include <stdbool.h>

#define is_even(x) ((x & 1) == 0)

static uint32_t gcd(uint32_t a, uint32_t b) {
    while (b != 0) {
        uint32_t temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

static bool is_possible(bucket_liters_t bucket_1_size,
                        bucket_liters_t bucket_2_size,
                        bucket_liters_t goal_volume) {
    if (goal_volume > bucket_1_size && goal_volume > bucket_2_size) return false;
    if (goal_volume % gcd(bucket_1_size, bucket_2_size) != 0) return false;
    return true;
}

bucket_result_t measure(bucket_liters_t bucket_1_size,
                        bucket_liters_t bucket_2_size,
                        bucket_liters_t goal_volume, bucket_id_t start_bucket) {
    bucket_result_t result = {0};
    result.possible = is_possible(bucket_1_size, bucket_2_size, goal_volume);
    if (!result.possible) return result;

    if (bucket_1_size == goal_volume) {
        result.goal_bucket = BUCKET_ID_1;
        result.move_count = 1;
        result.other_bucket_liters = 0;
        if (start_bucket == BUCKET_ID_2) {
            result.move_count = 2;
            result.other_bucket_liters = bucket_2_size;
        }
        return result;
    }

    if (bucket_2_size == goal_volume) {
        result.goal_bucket = BUCKET_ID_2;
        result.move_count = 1;
        result.other_bucket_liters = 0;
        if (start_bucket == BUCKET_ID_1) {
            result.move_count = 2;
            result.other_bucket_liters = bucket_1_size;
        }
        return result;
    }

    bucket_liters_t bucket_state[2] = {0, 0};
    bucket_liters_t bucket_size[2] = {bucket_1_size, bucket_2_size};
    bucket_id_t other_bucket = (bucket_id_t)!start_bucket;
    result.move_count = 0;

    while (bucket_state[0] != goal_volume && bucket_state[1] != goal_volume) {
        if (bucket_state[start_bucket] == 0) {
            bucket_state[start_bucket] = bucket_size[start_bucket];
            result.move_count++;
        } else if (bucket_state[other_bucket] == bucket_size[other_bucket]) {
            bucket_state[other_bucket] = 0;
            result.move_count++;
        } else {
            bucket_liters_t pour_amount = (bucket_size[other_bucket] - bucket_state[other_bucket]);
            if (bucket_state[start_bucket] <= pour_amount) {
                bucket_state[other_bucket] += bucket_state[start_bucket];
                bucket_state[start_bucket] = 0;
            } else {
                bucket_state[other_bucket] = bucket_size[other_bucket];
                bucket_state[start_bucket] -= pour_amount;
            }
            result.move_count++;
        }
    }

    result.goal_bucket = (bucket_state[0] == goal_volume) ? BUCKET_ID_1 : BUCKET_ID_2;
    result.other_bucket_liters = bucket_state[!result.goal_bucket];

    return result;
}