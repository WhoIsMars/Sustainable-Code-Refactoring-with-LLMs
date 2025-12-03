#include "high_scores.h"

int32_t latest(const int32_t* scores, size_t scores_len) {
    return scores[scores_len - 1];
}

int32_t personal_best(const int32_t* scores, size_t scores_len) {
    int32_t best = scores[0];
    for (size_t i = 1; i < scores_len; ++i) {
        if (scores[i] > best) {
            best = scores[i];
        }
    }

    return best;
}

size_t personal_top_three(const int32_t* scores, size_t scores_len, int32_t* output) {
    size_t output_len = 0;
    for (size_t i = 0; i < scores_len; ++i) {
        if (scores[i] > output[0]) {
            output[2] = output[1];
            output[1] = output[0];
            output[0] = scores[i];
        } else if (scores[i] > output[1]) {
            output[2] = output[1];
            output[1] = scores[i];
        } else if (scores[i] > output[2]) {
            output[2] = scores[i];
        }

        if (output_len < 3) {
            ++output_len;
        }
    }

    return output_len;
}
