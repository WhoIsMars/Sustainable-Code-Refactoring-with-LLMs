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
  if (bucket_1_size == 0 && bucket_2_size == 0) {
    return goal_volume == 0;
  }
  if (bucket_1_size == 0) {
    return goal_volume <= bucket_2_size;
  }
  if (bucket_2_size == 0) {
    return goal_volume <= bucket_1_size;
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

  bucket_liters_t bucket_a_size = (start_bucket == BUCKET_ID_1) ? bucket_1_size : bucket_2_size;
  bucket_liters_t bucket_b_size = (start_bucket == BUCKET_ID_1) ? bucket_2_size : bucket_1_size;
  bucket_liters_t bucket_a = 0;
  bucket_liters_t bucket_b = 0;
  result.move_count = 0;

  while (bucket_a != goal_volume && bucket_b != goal_volume) {
    if (bucket_a == 0) {
      bucket_a = bucket_a_size;
      result.move_count++;
    } else if (bucket_b == bucket_b_size) {
      bucket_b = 0;
      result.move_count++;
    } else {
      bucket_liters_t pour_amount = (bucket_a <= (bucket_b_size - bucket_b)) ? bucket_a : (bucket_b_size - bucket_b);
      bucket_a -= pour_amount;
      bucket_b += pour_amount;
      result.move_count++;
    }
  }

  result.goal_bucket = (bucket_a == goal_volume) ? start_bucket : (bucket_id_t)!start_bucket;
  result.other_bucket_liters = (result.goal_bucket == BUCKET_ID_1) ? bucket_b : bucket_a;

  return result;
}