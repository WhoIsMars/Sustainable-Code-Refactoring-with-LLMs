#include "two_bucket.h"

static int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

static bucket_result_t solve_bucket_problem(bucket_liters_t size1, bucket_liters_t size2, 
                                          bucket_liters_t goal, bucket_id_t start) {
    bucket_result_t result = {0};
    
    if (goal > (size1 > size2 ? size1 : size2) || goal % gcd(size1, size2) != 0) {
        result.possible = false;
        return result;
    }
    
    if (goal == 0) {
        result.possible = true;
        result.move_count = 0;
        result.goal_bucket = start;
        result.other_bucket_liters = 0;
        return result;
    }
    
    bucket_liters_t current1 = 0, current2 = 0;
    int moves = 0;
    bucket_liters_t first_size = (start == BUCKET_ID_1) ? size1 : size2;
    bucket_liters_t second_size = (start == BUCKET_ID_1) ? size2 : size1;
    
    current1 = first_size;
    moves++;
    
    while (current1 != goal && current2 != goal) {
        bucket_liters_t pour_amount = (current1 < second_size - current2) ? current1 : second_size - current2;
        current2 += pour_amount;
        current1 -= pour_amount;
        moves++;
        
        if (current1 == goal || current2 == goal) break;
        
        if (current2 == second_size) {
            current2 = 0;
            moves++;
        } else if (current1 == 0) {
            current1 = first_size;
            moves++;
        }
    }
    
    result.possible = true;
    result.move_count = moves;
    result.goal_bucket = (current1 == goal) ? start : (start == BUCKET_ID_1 ? BUCKET_ID_2 : BUCKET_ID_1);
    result.other_bucket_liters = (current1 == goal) ? current2 : current1;
    
    return result;
}

bucket_result_t measure(bucket_liters_t bucket_1_size,
                        bucket_liters_t bucket_2_size,
                        bucket_liters_t goal_volume,
                        bucket_id_t start_bucket)
{
    return solve_bucket_problem(bucket_1_size, bucket_2_size, goal_volume, start_bucket);
}