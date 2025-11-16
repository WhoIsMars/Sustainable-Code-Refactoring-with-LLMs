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

struct state_hash {
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
        state current = queue.front();
        queue.pop();

        if (visited.count(current)) {
            continue;
        }

        if (current.a == target_volume || current.b == target_volume) {
            measure_result result;
            result.goal_bucket = (current.a == target_volume) ? bucket_id::one : bucket_id::two;
            result.num_moves = current.steps;
            result.other_bucket_volume = (current.a == target_volume) ? current.b : current.a;
            return result;
        }

        visited.insert(current);

        const int a = current.a;
        const int b = current.b;
        const int steps = current.steps + 1;

        state candidates[] = {
            {bucket1_capacity, b, steps},
            {a, bucket2_capacity, steps},
            {a - std::min(a, bucket2_capacity - b), b + std::min(a, bucket2_capacity - b), steps},
            {a + std::min(b, bucket1_capacity - a), b - std::min(b, bucket1_capacity - a), steps},
            {0, b, steps},
            {a, 0, steps}
        };

        for (const auto& candidate : candidates) {
            if (candidate.a >= 0 && candidate.a <= bucket1_capacity &&
                candidate.b >= 0 && candidate.b <= bucket2_capacity &&
                (candidate.a != a || candidate.b != b) &&
                !visited.count(candidate) &&
                is_valid_state(candidate, bucket1_capacity, bucket2_capacity, start_bucket)) {
                queue.push(candidate);
            }
        }
    }

    throw std::domain_error("no solution found.");
}

}  // namespace two_bucket