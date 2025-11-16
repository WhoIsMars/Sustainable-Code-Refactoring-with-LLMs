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
        visited.insert(current);

        if (current.a == target_volume || current.b == target_volume) {
            return {
                current.a == target_volume ? bucket_id::one : bucket_id::two,
                current.steps,
                current.a == target_volume ? current.b : current.a
            };
        }

        auto a = current.a, b = current.b, steps = current.steps;

        if (a != bucket1_capacity) queue.push({bucket1_capacity, b, steps + 1});
        if (b != bucket2_capacity) queue.push({a, bucket2_capacity, steps + 1});
        if (a != 0) queue.push({0, b, steps + 1});
        if (b != 0) queue.push({a, 0, steps + 1});

        if (b != bucket2_capacity && a != 0) {
            int delta = std::min(a, bucket2_capacity - b);
            queue.push({a - delta, b + delta, steps + 1});
        }
        if (a != bucket1_capacity && b != 0) {
            int delta = std::min(b, bucket1_capacity - a);
            queue.push({a + delta, b - delta, steps + 1});
        }
    }

    throw std::domain_error("no solution found.");
}

}  // namespace two_bucket