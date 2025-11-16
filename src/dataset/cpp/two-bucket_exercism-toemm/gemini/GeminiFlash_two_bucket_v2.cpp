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

    std::set<state> visited;
    std::queue<state> queue;
    state initial_state{0, 0, 1}; 

    if (start_bucket == bucket_id::one) {
        initial_state.a = bucket1_capacity;
    } else {
        initial_state.b = bucket2_capacity;
    }

    queue.push(initial_state);
    visited.insert({0,0,0});

    while (!queue.empty()) {
        state current_state = queue.front();
        queue.pop();

        if (current_state.a == target_volume) {
            return {bucket_id::one, current_state.steps, current_state.b};
        }
        if (current_state.b == target_volume) {
            return {bucket_id::two, current_state.steps, current_state.a};
        }

        // Possible next states: fill, empty, pour
        std::vector<state> next_states;

        // Fill bucket A
        state fill_a = current_state;
        fill_a.a = bucket1_capacity;
        fill_a.steps++;
        if (visited.find({fill_a.a, fill_a.b, 0}) == visited.end()) next_states.push_back(fill_a);

        // Fill bucket B
        state fill_b = current_state;
        fill_b.b = bucket2_capacity;
        fill_b.steps++;
        if (visited.find({fill_b.a, fill_b.b, 0}) == visited.end()) next_states.push_back(fill_b);

        // Empty bucket A
        state empty_a = current_state;
        empty_a.a = 0;
        empty_a.steps++;
        if (visited.find({empty_a.a, empty_a.b, 0}) == visited.end()) next_states.push_back(empty_a);

        // Empty bucket B
        state empty_b = current_state;
        empty_b.b = 0;
        empty_b.steps++;
        if (visited.find({empty_b.a, empty_b.b, 0}) == visited.end()) next_states.push_back(empty_b);

        // Pour A into B
        state pour_a_to_b = current_state;
        int pour_amount = std::min(pour_a_to_b.a, bucket2_capacity - pour_a_to_b.b);
        pour_a_to_b.a -= pour_amount;
        pour_a_to_b.b += pour_amount;
        pour_a_to_b.steps++;
        if (visited.find({pour_a_to_b.a, pour_a_to_b.b, 0}) == visited.end()) next_states.push_back(pour_a_to_b);

        // Pour B into A
        state pour_b_to_a = current_state;
        pour_amount = std::min(pour_b_to_a.b, bucket1_capacity - pour_b_to_a.a);
        pour_b_to_a.a += pour_amount;
        pour_b_to_a.b -= pour_amount;
        pour_b_to_a.steps++;
        if (visited.find({pour_b_to_a.a, pour_b_to_a.b, 0}) == visited.end()) next_states.push_back(pour_b_to_a);

        for (const auto& next_state : next_states) {
            if ( (next_state.a == 0 && next_state.b == bucket2_capacity) || (next_state.b == 0 && next_state.a == bucket1_capacity)) {
                if (start_bucket == bucket_id::one && (next_state.a == 0 && next_state.b == bucket2_capacity)) continue;
                if (start_bucket == bucket_id::two && (next_state.b == 0 && next_state.a == bucket1_capacity)) continue;
            }
            
            if (visited.insert({next_state.a, next_state.b, 0}).second) {
                queue.push(next_state);
            }
        }
    }

    throw std::domain_error("no solution found.");
}
}  // namespace two_bucket