#include "two_bucket.h"

#include <stdint.h>

#define is_even(x) (((x) & 1) == 0)
#define BUCKET_NUM (2)

static uint32_t gcd(uint32_t a, uint32_t b) {
  if (a == 0) {
    return b;
  }
  if (b == 0) {
    return a;
  }

  uint32_t shift = 0;
  while (((a | b) & 1) == 0) {
    shift++;
    a >>= 1;
    b >>= 1;
  }

  while ((a & 1) == 0) {
    a >>= 1;
  }

  do {
    while ((b & 1) == 0) {
      b >>= 1;
    }

    if (a > b) {
      uint32_t temp = a;
      a = b;
      b = temp;
    }

    b = b - a;
  } while (b != 0);

  return a << shift;
}

static bool is_possible(bucket_liters_t bucket_1_size,
                        bucket_liters_t bucket_2_size,
                        bucket_liters_t goal_volume) {
  if (goal_volume > bucket_1_size && goal_volume > bucket_2_size) {
    return false;
  }
  return (goal_volume % gcd(bucket_1_size, bucket_2_size) == 0);
}

bucket_result_t measure(bucket_liters_t bucket_1_size,
                        bucket_liters_t bucket_2_size,
                        bucket_liters_t goal_volume, bucket_id_t start_bucket) {
  bucket_result_t result = {0};

  if (!(result.possible = is_possible(bucket_1_size, bucket_2_size, goal_volume))) {
    return result;
  }

  if (bucket_1_size == goal_volume) {
    result.goal_bucket = BUCKET_ID_1;
    result.move_count = 1;
    result.other_bucket_liters = 0;
    return result;
  } else if (bucket_2_size == goal_volume) {
    result.goal_bucket = BUCKET_ID_2;
    result.move_count = 1;
    result.other_bucket_liters = 0;
    return result;
  }

  bucket_liters_t bucket_state[2] = {0, 0};
  bucket_liters_t bucket_size[2] = {bucket_1_size, bucket_2_size};

  bucket_state[start_bucket] = bucket_size[start_bucket];
  result.move_count = 1;

  bucket_id_t other_bucket = (bucket_id_t)!start_bucket;

  while (bucket_state[0] != goal_volume && bucket_state[1] != goal_volume) {
    if (bucket_state[start_bucket] == goal_volume) break;
    if (bucket_state[start_bucket] == 0) {
      bucket_state[start_bucket] = bucket_size[start_bucket];
      result.move_count++;
    } else if (bucket_state[other_bucket] != bucket_size[other_bucket]) {
      bucket_liters_t pour_amount =
          (bucket_size[other_bucket] - bucket_state[other_bucket] <
           bucket_state[start_bucket])
              ? (bucket_size[other_bucket] - bucket_state[other_bucket])
              : bucket_state[start_bucket];

      bucket_state[other_bucket] += pour_amount;
      bucket_state[start_bucket] -= pour_amount;
      result.move_count++;

    } else {
      bucket_state[other_bucket] = 0;
      result.move_count++;
    }
  }

  result.goal_bucket =
      (bucket_state[0] == goal_volume) ? BUCKET_ID_1 : BUCKET_ID_2;
  result.other_bucket_liters = bucket_state[!result.goal_bucket];

  return result;
}