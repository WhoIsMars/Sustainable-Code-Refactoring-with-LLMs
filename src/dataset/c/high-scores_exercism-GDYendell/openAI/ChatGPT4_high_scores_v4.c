#include "high_scores.h"
#include <string.h>

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
    int32_t top_three[3] = {INT32_MIN, INT32_MIN, INT32_MIN};
    size_t limit = scores_len < 3 ? scores_len : 3;

    for (size_t i = 0; i < scores_len; ++i) {
        if (scores[i] > top_three[0]) {
            top_three[2] = top_three[1];
            top_three[1] = top_three[0];
            top_three[0] = scores[i];
        } else if (scores[i] > top_three[1]) {
            top_three[2] = top_three[1];
            top_three[1] = scores[i];
        } else if (scores[i] > top_three[2]) {
            top_three[2] = scores[i];
        }
    }

    memcpy(output, top_three, limit * sizeof(int32_t));
    return limit;
}