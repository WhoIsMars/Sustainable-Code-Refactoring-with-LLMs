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
    } else {
        return !(st.b == 0 && st.a == bucket1_cap);
    }
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

    while (!queue.empty()) {
        state current_state = queue.front();
        queue.pop();

        if (visited.count(current_state)) {
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
            {bucket1_capacity, b, steps},  // fill bucket 1
            {a, bucket2_capacity, steps},  // fill bucket 2
            {0, b, steps},                 // empty bucket 1
            {a, 0, steps},                 // empty bucket 2
            {0, 0, 0},                     // pour a to b (placeholder)
            {0, 0, 0}                      // pour b to a (placeholder)
        };

        // Pour a to b
        if (b < bucket2_capacity && a > 0) {
            int delta = std::min(a, bucket2_capacity - b);
            candidates[4] = {a - delta, b + delta, steps};
        } else {
            candidates[4] = {-1, -1, -1}; // invalid marker
        }

        // Pour b to a
        if (a < bucket1_capacity && b > 0) {
            int delta = std::min(b, bucket1_capacity - a);
            candidates[5] = {a + delta, b - delta, steps};
        } else {
            candidates[5] = {-1, -1, -1}; // invalid marker
        }

        for (int i = 0; i < 6; ++i) {
            const state& candidate = candidates[i];
            
            // Skip invalid states
            if (candidate.a < 0 || candidate.b < 0) continue;
            
            // Skip if same as current state
            if (candidate.a == a && candidate.b == b) continue;
            
            // Skip if already visited
            if (visited.count(candidate)) continue;
            
            // Skip if invalid according to problem rules
            if (!is_valid_state(candidate, bucket1_capacity, bucket2_capacity, start_bucket)) continue;
            
            queue.push(candidate);
        }
    }

    throw std::domain_error("no solution found.");
}

}  // namespace two_bucket