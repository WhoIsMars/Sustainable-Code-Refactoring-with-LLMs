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

    // Calculate total size to reserve output map
    size_t total_size = std::transform_reduce(
        std::execution::par_unseq, texts.begin(), texts.end(),
        size_t{0}, std::plus<>{},
        [](const std::string_view& text) { return text.size(); }
    );

    // Use single map with mutex for smaller datasets, parallel reduction for larger
    if (total_size < 10000) {
        std::unordered_map<char, int> result;
        result.reserve(26); // Reserve for alphabet
        
        for (const auto& text : texts) {
            for (char c : text) {
                if (std::isalpha(c)) {
                    ++result[std::tolower(c)];
                }
            }
        }
        return result;
    }

    // Parallel approach for larger datasets
    std::vector<std::unordered_map<char, int>> thread_maps(texts.size());
    
    // Pre-reserve maps to reduce allocations
    for (auto& map : thread_maps) {
        map.reserve(26);
    }

    std::vector<size_t> indices(texts.size());
    std::iota(indices.begin(), indices.end(), 0);

    std::for_each(std::execution::par_unseq, indices.begin(), indices.end(), 
        [&thread_maps, &texts](size_t index) {
            const auto& text = texts[index];
            auto& local_map = thread_maps[index];

            for (char c : text) {
                if (std::isalpha(c)) {
                    ++local_map[std::tolower(c)];
                }
            }
        });

    // Merge with reserved capacity
    std::unordered_map<char, int> result;
    result.reserve(26);

    for (const auto& map : thread_maps) {
        for (const auto& [ch, count] : map) {
            result[ch] += count;
        }
    }

    return result;
}

}