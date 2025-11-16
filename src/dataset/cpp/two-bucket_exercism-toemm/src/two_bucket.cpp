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


bool is_valid_state(state st, int bucket1_cap, int bucket2_cap, bucket_id start_bucket) {

    switch (start_bucket)
    {
    case bucket_id::one:
        if (st.a == 0 && st.b == bucket2_cap) return false;
        else return true;

    case bucket_id::two:
        if (st.b == 0 && st.a == bucket1_cap) return false;
        else return true;
    }

    return false;

}

measure_result measure(int bucket1_capacity, int bucket2_capacity,
    int target_volume, bucket_id start_bucket) {

    std::set<state> visited;
    state starting_state{0, 0, 0};
    std::queue<state> queue;
    measure_result result;

    if (target_volume > bucket1_capacity && target_volume > bucket2_capacity) {
        throw std::domain_error("goal higher than capacity");
    }

    // starting state
    switch (start_bucket)
    {
    case bucket_id::one:
        starting_state.a = bucket1_capacity;
        break;
    case bucket_id::two:
        starting_state.b = bucket2_capacity;
        break;
    }
    starting_state.steps++;


    // push the starting state to queue
    queue.push(starting_state);

    // go through the deck
    while (1) {

        // exhausted all possibilities
        if (queue.empty() == true) throw std::domain_error("no solution found.");

        // get newest state
        state new_state = queue.front();

        // already went there
        if (visited.find(new_state) != visited.end()) {

            // pop this element from the queue
            queue.pop();
            continue;

        // found a new state
        } else {

            // check if goal is reached
            if (new_state.a == target_volume || new_state.b == target_volume) {
                result.goal_bucket = new_state.a == target_volume ? bucket_id::one : bucket_id::two;
                result.num_moves = new_state.steps;
                result.other_bucket_volume = new_state.a == target_volume ? new_state.b : new_state.a;
                break;

            // perform an action
            } else {

                auto a = new_state.a;
                auto b = new_state.b;
                auto steps = new_state.steps;
                std::vector<state> states;

                
                // fill up bucket
                if (a != bucket1_capacity) {
                    states.push_back({bucket1_capacity, b, steps+1});
                }  
                
                if (b != bucket2_capacity) {
                    states.push_back({a, bucket2_capacity, steps+1});
                }


                // pour bucket

                // a pour to b
                if (b != bucket2_capacity && a != 0) {

                    auto delta = std::min(a, bucket2_capacity - b);
                    states.push_back({a - delta, b + delta, steps + 1});

                // b pour to a
                } 

                if (a != bucket1_capacity && b != 0) {

                    auto delta = std::min(b, bucket1_capacity - a);
                    states.push_back({a + delta, b - delta, steps+1});
                }


                // empty bucket

                if (a != 0) {
                    states.push_back({0, b, steps+1});
                } 
                
                if (b != 0) {
                    states.push_back({a, 0, steps+1});
                }



                // remove illegal states from states vector
                states.erase(std::remove_if(states.begin(), states.end(), 
                                [bucket1_capacity, bucket2_capacity, start_bucket]
                                (state st) 
                            {
                                return !is_valid_state(st, bucket1_capacity, bucket2_capacity, start_bucket);
                            }), states.end());

                // add to queue 
                for (auto e : states) {
                    queue.push(e);

                }

                queue.pop();
            }
        }

        // add the currently visited state to visited set
        visited.insert(new_state);
    }

    return result;

}
}  // namespace two_bucket
