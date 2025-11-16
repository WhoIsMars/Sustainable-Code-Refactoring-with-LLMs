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

    // Calculate total size to reserve memory
    size_t total_size = std::accumulate(texts.begin(), texts.end(), size_t{0},
        [](size_t sum, const std::string_view& text) {
            return sum + text.size();
        });

    // Use fewer threads for small datasets
    const size_t min_work_per_thread = 1000;
    size_t num_threads = std::min(texts.size(), 
        std::max(size_t{1}, total_size / min_work_per_thread));

    std::vector<std::unordered_map<char, int>> thread_maps(num_threads);
    
    // Pre-reserve buckets based on expected alphabet size
    for (auto& map : thread_maps) {
        map.reserve(26);
    }

    std::vector<size_t> indices(texts.size());
    std::iota(indices.begin(), indices.end(), 0);

    std::for_each(std::execution::par_unseq, indices.begin(), indices.end(), 
        [&thread_maps, &texts, num_threads](size_t index) {
            const auto& text = texts[index];
            auto& local_map = thread_maps[index % num_threads];

            for (char c : text) {
                if (std::isalpha(static_cast<unsigned char>(c))) {
                    ++local_map[std::tolower(static_cast<unsigned char>(c))];
                }
            }
        });

    // Merge with reserved capacity
    std::unordered_map<char, int> out;
    out.reserve(26);

    for (const auto& map : thread_maps) {
        for (const auto& [ch, count] : map) {
            out[ch] += count;
        }
    }
    
    return out;
}

}