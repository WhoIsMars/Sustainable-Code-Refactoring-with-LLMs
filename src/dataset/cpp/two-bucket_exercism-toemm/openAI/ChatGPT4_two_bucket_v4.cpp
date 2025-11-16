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
    std::size_t operator()(const state& st) const {
        return std::hash<int>()(st.a) ^ (std::hash<int>()(st.b) << 1);
    }
};

bool is_valid_state(const state& st, int bucket1_cap, int bucket2_cap, bucket_id start_bucket) {
    if (start_bucket == bucket_id::one) {
        return !(st.a == 0 && st.b == bucket2_cap);
    } else {
        return !(st.b == 0 && st.a == bucket1_cap);
    }
}

measure_result measure(int bucket1_capacity, int bucket2_capacity, int target_volume, bucket_id start_bucket) {
    if (target_volume > bucket1_capacity && target_volume > bucket2_capacity) {
        throw std::domain_error("goal higher than capacity");
    }

    std::unordered_set<state, state_hash> visited;
    std::queue<state> queue;

    state starting_state = {0, 0, 1};
    if (start_bucket == bucket_id::one) {
        starting_state.a = bucket1_capacity;
    } else {
        starting_state.b = bucket2_capacity;
    }
    queue.push(starting_state);

    while (!queue.empty()) {
        state current = queue.front();
        queue.pop();

        if (visited.count(current)) continue;
        visited.insert(current);

        if (current.a == target_volume || current.b == target_volume) {
            return {
                current.a == target_volume ? bucket_id::one : bucket_id::two,
                current.steps,
                current.a == target_volume ? current.b : current.a
            };
        }

        std::vector<state> next_states;

        if (current.a != bucket1_capacity) next_states.push_back({bucket1_capacity, current.b, current.steps + 1});
        if (current.b != bucket2_capacity) next_states.push_back({current.a, bucket2_capacity, current.steps + 1});
        if (current.a != 0) next_states.push_back({0, current.b, current.steps + 1});
        if (current.b != 0) next_states.push_back({current.a, 0, current.steps + 1});

        if (current.a != 0 && current.b != bucket2_capacity) {
            int delta = std::min(current.a, bucket2_capacity - current.b);
            next_states.push_back({current.a - delta, current.b + delta, current.steps + 1});
        }
        if (current.b != 0 && current.a != bucket1_capacity) {
            int delta = std::min(current.b, bucket1_capacity - current.a);
            next_states.push_back({current.a + delta, current.b - delta, current.steps + 1});
        }

        for (const auto& next : next_states) {
            if (is_valid_state(next, bucket1_capacity, bucket2_capacity, start_bucket) && !visited.count(next)) {
                queue.push(next);
            }
        }
    }

    throw std::domain_error("no solution found.");
}

}  // namespace two_bucket