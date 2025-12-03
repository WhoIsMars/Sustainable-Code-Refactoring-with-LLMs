#include "high_scores.h"
#include <algorithm>

int32_t latest(const int32_t* scores, size_t scores_len) {
    return scores[scores_len - 1];
}

int32_t personal_best(const int32_t* scores, size_t scores_len) {
    int32_t best = 0;
    for (size_t i = 0; i < scores_len; ++i) {
        if (scores[i] > best) {
            best = scores[i];
        }
    }
    return best;
}

size_t personal_top_three(const int32_t* scores, size_t scores_len, int32_t* output) {
    size_t count = std::min((size_t)3, scores_len);

    if (scores_len == 0) {
        return 0;
    }

    int32_t temp_scores[scores_len];
    std::copy(scores, scores + scores_len, temp_scores);

    std::sort(temp_scores, temp_scores + scores_len, std::greater<int32_t>());

    for (size_t i = 0; i < count; ++i) {
        output[i] = temp_scores[i];
    }

    return count;
}