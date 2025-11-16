#include "parallel_letter_frequency.h"

#include <algorithm>
#include <execution>
#include <unordered_map>
#include <mutex>

namespace parallel_letter_frequency {

std::unordered_map<char, int> frequency(const std::vector<std::string_view>& texts) {
    std::unordered_map<char, int> out;
    std::mutex out_mutex;

    std::for_each(std::execution::par, texts.begin(), texts.end(),
        [&out, &out_mutex](const std::string_view& text) {
            std::unordered_map<char, int> local_map;

            for (char c : text) {
                if (std::isalpha(c)) {
                    local_map[std::tolower(c)]++;
                }
            }

            std::lock_guard<std::mutex> lock(out_mutex);
            for (const auto& [ch, count] : local_map) {
                out[ch] += count;
            }
        });

    return out;
}

}