#include "high_scores.h"

int32_t latest(const int32_t* scores, size_t scores_len) {
    return scores[scores_len - 1];
}

int32_t personal_best(const int32_t* scores, size_t scores_len) {
    int32_t best = scores[0];
    const int32_t* end = scores + scores_len;
    
    for (const int32_t* current = scores + 1; current < end; ++current) {
        if (*current > best) {
            best = *current;
        }
    }
    
    return best;
}

size_t personal_top_three(const int32_t* scores, size_t scores_len, int32_t* output) {
    if (scores_len == 0) return 0;
    
    output[0] = output[1] = output[2] = INT32_MIN;
    size_t output_len = (scores_len < 3) ? scores_len : 3;
    
    const int32_t* end = scores + scores_len;
    for (const int32_t* current = scores; current < end; ++current) {
        int32_t score = *current;
        
        if (score > output[0]) {
            output[2] = output[1];
            output[1] = output[0];
            output[0] = score;
        } else if (score > output[1]) {
            output[2] = output[1];
            output[1] = score;
        } else if (score > output[2]) {
            output[2] = score;
        }
    }
    
    return output_len;
}