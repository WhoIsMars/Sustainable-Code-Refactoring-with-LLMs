#include "two_bucket.h"

#include <stdexcept>
#include <queue>
#include <set>
#include <algorithm>
#include <tuple>

namespace two_bucket {

struct state {
    int a;
    int b;
    int steps;

    bool operator<(const state& other) const {
        return std::tie(a, b) < std::tie(other.a, other.b);
    }
};


measure_result measure(int bucket1_capacity, int bucket2_capacity,
    int target_volume, bucket_id start_bucket) {

    if (target_volume > bucket1_capacity && target_volume > bucket2_capacity) {
        throw std::domain_error("goal higher than capacity");
    }

    std::queue<state> queue;
    std::set<state> visited;

    state initial_state = {0, 0, 1};
    if (start_bucket == bucket_id::one) {
        initial_state.a = bucket1_capacity;
    } else {
        initial_state.b = bucket2_capacity;
    }

    queue.push(initial_state);
    visited.insert(initial_state);

    while (!queue.empty()) {
        state current_state = queue.front();
        queue.pop();

        if (current_state.a == target_volume) {
            return {bucket_id::one, current_state.steps, current_state.b};
        }
        if (current_state.b == target_volume) {
            return {bucket_id::two, current_state.steps, current_state.a};
        }

        // Possible next states
        std::vector<state> next_states;

        // Fill bucket A
        if (current_state.a < bucket1_capacity) {
            next_states.push_back({bucket1_capacity, current_state.b, current_state.steps + 1});
        }

        // Fill bucket B
        if (current_state.b < bucket2_capacity) {
            next_states.push_back({current_state.a, bucket2_capacity, current_state.steps + 1});
        }

        // Empty bucket A
        if (current_state.a > 0) {
            next_states.push_back({0, current_state.b, current_state.steps + 1});
        }

        // Empty bucket B
        if (current_state.b > 0) {
            next_states.push_back({current_state.a, 0, current_state.steps + 1});
        }

        // Pour A into B
        if (current_state.a > 0 && current_state.b < bucket2_capacity) {
            int pour_amount = std::min(current_state.a, bucket2_capacity - current_state.b);
            next_states.push_back({current_state.a - pour_amount, current_state.b + pour_amount, current_state.steps + 1});
        }

        // Pour B into A
        if (current_state.b > 0 && current_state.a < bucket1_capacity) {
            int pour_amount = std::min(current_state.b, bucket1_capacity - current_state.a);
            next_states.push_back({current_state.a + pour_amount, current_state.b - pour_amount, current_state.steps + 1});
        }

        for (const auto& next_state : next_states) {
            //Check for invalid states based on initial bucket fill
            bool is_valid = true;
            if (start_bucket == bucket_id::one && next_state.a == 0 && next_state.b == bucket2_capacity) {
                is_valid = false;
            } else if (start_bucket == bucket_id::two && next_state.b == 0 && next_state.a == bucket1_capacity) {
                is_valid = false;
            }

            if (is_valid && visited.find(next_state) == visited.end()) {
                queue.push(next_state);
                visited.insert(next_state);
            }
        }
    }

    throw std::domain_error("no solution found.");
}
}  // namespace two_bucket