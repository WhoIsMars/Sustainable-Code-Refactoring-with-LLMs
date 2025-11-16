#include "parallel_letter_frequency.h"

#include <algorithm>
#include <execution>
#include <unordered_map>
#include <vector>
#include <cctype>

namespace parallel_letter_frequency {

std::unordered_map<char, int> frequency(std::vector<std::string_view> texts) {
    std::unordered_map<char, int> out;
    if (texts.empty()) {
        return out;
    }

    std::for_each(std::execution::par, texts.begin(), texts.end(),
        [&out](std::string_view text) {
            std::unordered_map<char, int> local_map;
            for (char c : text) {
                if (std::isalpha(c)) {
                    local_map[tolower(c)]++;
                }
            }

            // Merge local_map into out using a mutex.  Since unordered_map
            // insertion is not thread-safe, protect it.  However, since
            // we're accumulating into a single map, the overhead of the
            // mutex can become significant.  A better approach would be
            // to use a concurrent hash map if available.  For now, we'll
            // use a mutex.
            std::lock_guard<std::mutex> lock(out_mutex);
            for (const auto& [ch, count] : local_map) {
                out[ch] += count;
            }
        });

    return out;
}

} // namespace parallel_letter_frequency