#include "two_bucket.h"

#include <stdexcept>
#include <queue>
#include <unordered_set>
#include <algorithm>

namespace two_bucket {

struct state {
    int a;
    int b;
    int steps;

    bool operator==(const state& other) const {
        return a == other.a && b == other.b;
    }
};

struct StateHash {
    std::size_t operator()(const state& s) const {
        return std::hash<int>()(s.a) ^ (std::hash<int>()(s.b) << 1);
    }
};

inline bool is_valid_state(const state& st, int bucket1_cap, int bucket2_cap, bucket_id start_bucket) {
    return !(start_bucket == bucket_id::one && st.a == 0 && st.b == bucket2_cap) &&
           !(start_bucket == bucket_id::two && st.b == 0 && st.a == bucket1_cap);
}

measure_result measure(int bucket1_capacity, int bucket2_capacity,
    int target_volume, bucket_id start_bucket) {

    if (target_volume > bucket1_capacity && target_volume > bucket2_capacity) {
        throw std::domain_error("goal higher than capacity");
    }

    std::unordered_set<state, StateHash> visited;
    std::queue<state> queue;
    
    state starting_state{0, 0, 1};
    if (start_bucket == bucket_id::one) {
        starting_state.a = bucket1_capacity;
    } else {
        starting_state.b = bucket2_capacity;
    }

    queue.push(starting_state);
    visited.reserve(1000);

    while (!queue.empty()) {
        state current = queue.front();
        queue.pop();

        if (visited.count(current)) {
            continue;
        }

        visited.insert(current);

        if (current.a == target_volume || current.b == target_volume) {
            measure_result result;
            result.goal_bucket = current.a == target_volume ? bucket_id::one : bucket_id::two;
            result.num_moves = current.steps;
            result.other_bucket_volume = current.a == target_volume ? current.b : current.a;
            return result;
        }

        int next_steps = current.steps + 1;
        state candidates[6];
        int count = 0;

        // Fill buckets
        if (current.a != bucket1_capacity) {
            candidates[count++] = {bucket1_capacity, current.b, next_steps};
        }
        if (current.b != bucket2_capacity) {
            candidates[count++] = {current.a, bucket2_capacity, next_steps};
        }

        // Pour between buckets
        if (current.b != bucket2_capacity && current.a != 0) {
            int delta = std::min(current.a, bucket2_capacity - current.b);
            candidates[count++] = {current.a - delta, current.b + delta, next_steps};
        }
        if (current.a != bucket1_capacity && current.b != 0) {
            int delta = std::min(current.b, bucket1_capacity - current.a);
            candidates[count++] = {current.a + delta, current.b - delta, next_steps};
        }

        // Empty buckets
        if (current.a != 0) {
            candidates[count++] = {0, current.b, next_steps};
        }
        if (current.b != 0) {
            candidates[count++] = {current.a, 0, next_steps};
        }

        for (int i = 0; i < count; ++i) {
            if (is_valid_state(candidates[i], bucket1_capacity, bucket2_capacity, start_bucket) &&
                !visited.count(candidates[i])) {
                queue.push(candidates[i]);
            }
        }
    }

    throw std::domain_error("no solution found.");
}

}  // namespace two_bucket