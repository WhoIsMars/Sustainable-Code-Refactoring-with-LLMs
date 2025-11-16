#include "two_bucket.h"

#include <stdexcept>
#include <queue>
#include <set>
#include <algorithm>
#include <tuple>
#include <iostream>

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
    std::set<std::pair<int, int>> visited;

    state initial_state = {0, 0, 1};
    if (start_bucket == bucket_id::one) {
        initial_state.a = bucket1_capacity;
    } else {
        initial_state.b = bucket2_capacity;
    }

    queue.push(initial_state);
    visited.insert({initial_state.a, initial_state.b});

    while (!queue.empty()) {
        state current_state = queue.front();
        queue.pop();

        if (current_state.a == target_volume) {
            return {bucket_id::one, current_state.steps, current_state.b};
        }
        if (current_state.b == target_volume) {
            return {bucket_id::two, current_state.steps, current_state.a};
        }

        // Possible next states:
        // 1. Fill bucket1
        state next_state1 = {bucket1_capacity, current_state.b, current_state.steps + 1};
        if (visited.find({next_state1.a, next_state1.b}) == visited.end()) {
            queue.push(next_state1);
            visited.insert({next_state1.a, next_state1.b});
        }

        // 2. Fill bucket2
        state next_state2 = {current_state.a, bucket2_capacity, current_state.steps + 1};
        if (visited.find({next_state2.a, next_state2.b}) == visited.end()) {
            queue.push(next_state2);
            visited.insert({next_state2.a, next_state2.b});
        }

        // 3. Empty bucket1
        state next_state3 = {0, current_state.b, current_state.steps + 1};
        if (visited.find({next_state3.a, next_state3.b}) == visited.end()) {
            queue.push(next_state3);
            visited.insert({next_state3.a, next_state3.b});
        }

        // 4. Empty bucket2
        state next_state4 = {current_state.a, 0, current_state.steps + 1};
        if (visited.find({next_state4.a, next_state4.b}) == visited.end()) {
            queue.push(next_state4);
            visited.insert({next_state4.a, next_state4.b});
        }

        // 5. Pour bucket1 into bucket2
        int pour_amount1 = std::min(current_state.a, bucket2_capacity - current_state.b);
        state next_state5 = {current_state.a - pour_amount1, current_state.b + pour_amount1, current_state.steps + 1};
        if (visited.find({next_state5.a, next_state5.b}) == visited.end()) {
            queue.push(next_state5);
            visited.insert({next_state5.a, next_state5.b});
        }

        // 6. Pour bucket2 into bucket1
        int pour_amount2 = std::min(current_state.b, bucket1_capacity - current_state.a);
        state next_state6 = {current_state.a + pour_amount2, current_state.b - pour_amount2, current_state.steps + 1};
        if (visited.find({next_state6.a, next_state6.b}) == visited.end()) {
            queue.push(next_state6);
            visited.insert({next_state6.a, next_state6.b});
        }
    }

    throw std::domain_error("no solution found.");
}
}  // namespace two_bucket