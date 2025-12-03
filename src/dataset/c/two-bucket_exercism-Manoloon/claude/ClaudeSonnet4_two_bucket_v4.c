#include "two_bucket.h"

static int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

bucket_result_t measure(bucket_liters_t bucket_1_size,
                        bucket_liters_t bucket_2_size,
                        bucket_liters_t goal_volume,
                        bucket_id_t start_bucket)
{
    bucket_result_t result = {0};
    
    if (goal_volume > bucket_1_size && goal_volume > bucket_2_size) {
        result.possible = false;
        return result;
    }
    
    if (goal_volume % gcd(bucket_1_size, bucket_2_size) != 0) {
        result.possible = false;
        return result;
    }
    
    if (goal_volume == bucket_1_size) {
        result.possible = true;
        result.goal_bucket = BUCKET_ID_1;
        result.move_count = (start_bucket == BUCKET_ID_1) ? 1 : 2;
        result.other_bucket_liters = (start_bucket == BUCKET_ID_1) ? 0 : bucket_2_size;
        return result;
    }
    
    if (goal_volume == bucket_2_size) {
        result.possible = true;
        result.goal_bucket = BUCKET_ID_2;
        result.move_count = (start_bucket == BUCKET_ID_2) ? 1 : 2;
        result.other_bucket_liters = (start_bucket == BUCKET_ID_2) ? 0 : bucket_1_size;
        return result;
    }
    
    bucket_liters_t b1 = 0, b2 = 0;
    int moves = 0;
    
    if (start_bucket == BUCKET_ID_1) {
        b1 = bucket_1_size;
        moves = 1;
    } else {
        b2 = bucket_2_size;
        moves = 1;
    }
    
    while (b1 != goal_volume && b2 != goal_volume) {
        bucket_liters_t pour = (b1 < bucket_2_size - b2) ? b1 : bucket_2_size - b2;
        
        if (b1 > 0 && b2 < bucket_2_size) {
            b2 += pour;
            b1 -= pour;
        } else if (b1 == 0) {
            b1 = bucket_1_size;
        } else if (b2 == bucket_2_size) {
            b2 = 0;
        }
        
        moves++;
        
        if (moves > bucket_1_size + bucket_2_size) break;
    }
    
    result.possible = true;
    result.goal_bucket = (b1 == goal_volume) ? BUCKET_ID_1 : BUCKET_ID_2;
    result.move_count = moves;
    result.other_bucket_liters = (b1 == goal_volume) ? b2 : b1;
    
    return result;
}