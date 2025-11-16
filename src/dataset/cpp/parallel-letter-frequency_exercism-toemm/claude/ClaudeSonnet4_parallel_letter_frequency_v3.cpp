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

    const size_t total_chars = std::transform_reduce(
        std::execution::par_unseq, texts.begin(), texts.end(), 
        size_t{0}, std::plus<>{}, 
        [](const std::string_view& text) { return text.size(); }
    );

    if (total_chars == 0) {
        return {};
    }

    std::unordered_map<char, int> result;
    result.reserve(26);

    const size_t chunk_size = std::max(size_t{1000}, total_chars / std::thread::hardware_concurrency());
    
    if (total_chars < chunk_size) {
        for (const auto& text : texts) {
            for (char c : text) {
                if (std::isalpha(c)) {
                    ++result[std::tolower(c)];
                }
            }
        }
        return result;
    }

    std::vector<std::unordered_map<char, int>> thread_maps(texts.size());
    
    std::for_each(std::execution::par_unseq, texts.begin(), texts.end(),
        [&thread_maps, &texts](const std::string_view& text) {
            const size_t index = &text - texts.data();
            auto& local_map = thread_maps[index];
            local_map.reserve(26);
            
            for (char c : text) {
                if (std::isalpha(c)) {
                    ++local_map[std::tolower(c)];
                }
            }
        });

    for (const auto& map : thread_maps) {
        for (const auto& [ch, count] : map) {
            result[ch] += count;
        }
    }

    return result;
}

}