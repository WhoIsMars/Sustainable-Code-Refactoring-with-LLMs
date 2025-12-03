#include "high_scores.h"

int32_t latest(const int32_t* scores, size_t scores_len) {
    return scores[scores_len - 1];
}

int32_t personal_best(const int32_t* scores, size_t scores_len) {
    int32_t best = scores[0];
    for (size_t i = 1; i < scores_len; ++i) {
        best = (scores[i] > best) ? scores[i] : best;
    }
    return best;
}

size_t personal_top_three(const int32_t* scores, size_t scores_len, int32_t* output) {
    int32_t top[3] = {INT32_MIN, INT32_MIN, INT32_MIN};
    size_t limit = (scores_len < 3) ? scores_len : 3;

    for (size_t i = 0; i < scores_len; ++i) {
        if (scores[i] > top[0]) {
            top[2] = top[1];
            top[1] = top[0];
            top[0] = scores[i];
        } else if (scores[i] > top[1]) {
            top[2] = top[1];
            top[1] = scores[i];
        } else if (scores[i] > top[2]) {
            top[2] = scores[i];
        }
    }

    for (size_t i = 0; i < limit; ++i) {
        output[i] = top[i];
    }

    return limit;
}