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

    std::set<std::pair<int, int>> visited;
    std::queue<state> queue;
    measure_result result;

    state starting_state{0, 0, 0};

    // starting state
    if (start_bucket == bucket_id::one) {
        starting_state.a = bucket1_capacity;
    } else {
        starting_state.b = bucket2_capacity;
    }
    starting_state.steps = 1;

    // push the starting state to queue
    queue.push(starting_state);
    visited.insert({starting_state.a, starting_state.b});

    // go through the deck
    while (!queue.empty()) {
        // get newest state
        state current_state = queue.front();
        queue.pop();

        // check if goal is reached
        if (current_state.a == target_volume) {
            result.goal_bucket = bucket_id::one;
            result.num_moves = current_state.steps;
            result.other_bucket_volume = current_state.b;
            return result;
        } else if (current_state.b == target_volume) {
            result.goal_bucket = bucket_id::two;
            result.num_moves = current_state.steps;
            result.other_bucket_volume = current_state.a;
            return result;
        }

        // perform actions and enqueue new states

        // fill bucket 1
        if (current_state.a < bucket1_capacity) {
            state next_state = {bucket1_capacity, current_state.b, current_state.steps + 1};
            if (visited.find({next_state.a, next_state.b}) == visited.end()) {
                queue.push(next_state);
                visited.insert({next_state.a, next_state.b});
            }
        }

        // fill bucket 2
        if (current_state.b < bucket2_capacity) {
            state next_state = {current_state.a, bucket2_capacity, current_state.steps + 1};
            if (visited.find({next_state.a, next_state.b}) == visited.end()) {
                queue.push(next_state);
                visited.insert({next_state.a, next_state.b});
            }
        }

        // empty bucket 1
        if (current_state.a > 0) {
            state next_state = {0, current_state.b, current_state.steps + 1};
            if (visited.find({next_state.a, next_state.b}) == visited.end()) {
                queue.push(next_state);
                visited.insert({next_state.a, next_state.b});
            }
        }

        // empty bucket 2
        if (current_state.b > 0) {
            state next_state = {current_state.a, 0, current_state.steps + 1};
            if (visited.find({next_state.a, next_state.b}) == visited.end()) {
                queue.push(next_state);
                visited.insert({next_state.a, next_state.b});
            }
        }

        // pour bucket 1 into bucket 2
        if (current_state.a > 0 && current_state.b < bucket2_capacity) {
            int pour_amount = std::min(current_state.a, bucket2_capacity - current_state.b);
            state next_state = {current_state.a - pour_amount, current_state.b + pour_amount, current_state.steps + 1};
            if (visited.find({next_state.a, next_state.b}) == visited.end()) {
                queue.push(next_state);
                visited.insert({next_state.a, next_state.b});
            }
        }

        // pour bucket 2 into bucket 1
        if (current_state.b > 0 && current_state.a < bucket1_capacity) {
            int pour_amount = std::min(current_state.b, bucket1_capacity - current_state.a);
            state next_state = {current_state.a + pour_amount, current_state.b - pour_amount, current_state.steps + 1};
            if (visited.find({next_state.a, next_state.b}) == visited.end()) {
                queue.push(next_state);
                visited.insert({next_state.a, next_state.b});
            }
        }
    }

    throw std::domain_error("no solution found.");
}
}  // namespace two_bucket