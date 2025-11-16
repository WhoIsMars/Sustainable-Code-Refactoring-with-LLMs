#include "two_bucket.h"

#include <stdexcept>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include <tuple>

namespace two_bucket {

struct state {
    int a;
    int b;
    int steps;

    bool operator==(const state& other) const {
        return a == other.a && b == other.b;
    }
};

struct state_hash {
    std::size_t operator()(const state& s) const {
        return std::hash<int>()(s.a) ^ (std::hash<int>()(s.b) << 1);
    }
};

inline bool is_valid_state(const state& st, int bucket1_cap, int bucket2_cap, bucket_id start_bucket) {
    if (start_bucket == bucket_id::one) {
        return !(st.a == 0 && st.b == bucket2_cap);
    }
    return !(st.b == 0 && st.a == bucket1_cap);
}

measure_result measure(int bucket1_capacity, int bucket2_capacity,
    int target_volume, bucket_id start_bucket) {

    if (target_volume > bucket1_capacity && target_volume > bucket2_capacity) {
        throw std::domain_error("goal higher than capacity");
    }

    std::unordered_set<state, state_hash> visited;
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
        state current_state = queue.front();
        queue.pop();

        if (visited.find(current_state) != visited.end()) {
            continue;
        }

        visited.insert(current_state);

        if (current_state.a == target_volume || current_state.b == target_volume) {
            measure_result result;
            result.goal_bucket = current_state.a == target_volume ? bucket_id::one : bucket_id::two;
            result.num_moves = current_state.steps;
            result.other_bucket_volume = current_state.a == target_volume ? current_state.b : current_state.a;
            return result;
        }

        const int a = current_state.a;
        const int b = current_state.b;
        const int steps = current_state.steps + 1;

        state candidates[6] = {
            {bucket1_capacity, b, steps},
            {a, bucket2_capacity, steps},
            {a - std::min(a, bucket2_capacity - b), b + std::min(a, bucket2_capacity - b), steps},
            {a + std::min(b, bucket1_capacity - a), b - std::min(b, bucket1_capacity - a), steps},
            {0, b, steps},
            {a, 0, steps}
        };

        bool valid[6] = {
            a != bucket1_capacity,
            b != bucket2_capacity,
            b != bucket2_capacity && a != 0,
            a != bucket1_capacity && b != 0,
            a != 0,
            b != 0
        };

        for (int i = 0; i < 6; ++i) {
            if (valid[i] && is_valid_state(candidates[i], bucket1_capacity, bucket2_capacity, start_bucket)) {
                queue.push(candidates[i]);
            }
        }
    }

    throw std::domain_error("no solution found.");
}

}  // namespace two_bucket