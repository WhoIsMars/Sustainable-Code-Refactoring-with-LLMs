#include "parallel_letter_frequency.h"

#include <algorithm>
#include <execution>
#include <unordered_map>
#include <numeric>

namespace parallel_letter_frequency {

std::unordered_map<char, int> frequency(std::vector<std::string_view> texts) {
    if (texts.empty()) {
        return {};
    }

    const size_t total_chars = std::accumulate(texts.begin(), texts.end(), size_t{0},
        [](size_t sum, const std::string_view& text) {
            return sum + text.size();
        });

    if (total_chars == 0) {
        return {};
    }

    constexpr size_t min_chars_per_thread = 1000;
    const size_t num_threads = std::min(texts.size(), 
        std::max(size_t{1}, total_chars / min_chars_per_thread));

    std::vector<std::unordered_map<char, int>> thread_maps(num_threads);
    
    std::vector<size_t> indices(texts.size());
    std::iota(indices.begin(), indices.end(), 0);

    std::for_each(std::execution::par_unseq, indices.begin(), indices.end(),
        [&thread_maps, &texts, num_threads](size_t index) {
            const size_t thread_id = index % num_threads;
            auto& local_map = thread_maps[thread_id];
            
            for (char c : texts[index]) {
                if (std::isalpha(static_cast<unsigned char>(c))) {
                    ++local_map[std::tolower(static_cast<unsigned char>(c))];
                }
            }
        });

    std::unordered_map<char, int> result;
    result.reserve(26);

    for (const auto& thread_map : thread_maps) {
        for (const auto& [ch, count] : thread_map) {
            result[ch] += count;
        }
    }

    return result;
}

}