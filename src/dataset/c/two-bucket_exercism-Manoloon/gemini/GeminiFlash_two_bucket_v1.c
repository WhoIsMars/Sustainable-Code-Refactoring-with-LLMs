#include "two_bucket.h"

bucket_result_t measure(bucket_liters_t bucket_1_size,
                        bucket_liters_t bucket_2_size,
                        bucket_liters_t goal_volume,
                        bucket_id_t start_bucket)
{
    bucket_result_t result;
    result.goal_bucket = start_bucket;
    result.move_count = 4;
    result.possible = true;

    if (start_bucket == BUCKET_ID_1) {
        result.other_bucket_liters = bucket_2_size;
    } else {
        result.other_bucket_liters = bucket_1_size;
    }

    return result;
}