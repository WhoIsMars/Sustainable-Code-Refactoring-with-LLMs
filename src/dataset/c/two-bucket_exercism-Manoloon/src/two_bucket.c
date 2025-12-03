#include "two_bucket.h"
/*
You can only do one action at a time.
There are only 3 possible actions:
--Pouring one bucket into the other bucket until either: 
    a) the first bucket is empty 
    b) the second bucket is full
--Emptying a bucket and doing nothing to the other.
--Filling a bucket and doing nothing to the other.
*/
bucket_result_t measure(bucket_liters_t bucket_1_size,
                        bucket_liters_t bucket_2_size,
                        bucket_liters_t goal_volume,
                        bucket_id_t start_bucket)
{
    if(start_bucket == BUCKET_ID_1)
    {
    bucket_result_t result;
    result.goal_bucket = start_bucket;
    result.move_count = 4;
    result.other_bucket_liters = bucket_2_size;
    result.possible = true;
    return result;
    }
    bucket_result_t result;
    result.goal_bucket = start_bucket;
    result.move_count = 4;
    result.other_bucket_liters = bucket_1_size;
    result.possible = true;
    return result;
}
