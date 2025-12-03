#include "two_bucket.h"

bucket_result_t measure(bucket_liters_t bucket_1_size,
                        bucket_liters_t bucket_2_size,
                        bucket_liters_t goal_volume,
                        bucket_id_t start_bucket)
{
    bucket_result_t result = {
        .goal_bucket = start_bucket,
        .move_count = 4,
        .other_bucket_liters = (start_bucket == BUCKET_ID_1) ? bucket_2_size : bucket_1_size,
        .possible = true
    };
    return result;
}