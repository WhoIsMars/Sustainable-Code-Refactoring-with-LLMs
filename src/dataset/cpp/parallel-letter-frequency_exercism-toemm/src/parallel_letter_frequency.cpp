#include "parallel_letter_frequency.h"

#include <algorithm>
#include <execution>
#include <unordered_map>

namespace parallel_letter_frequency {


std::unordered_map<char, int> frequency(std::vector<std::string_view> texts) {

    std::vector<size_t> indices(texts.size());
    std::iota(indices.begin(), indices.end(), 0);

    std::vector<std::unordered_map<char, int>> thread_maps(texts.size());


    std::for_each(std::execution::par, indices.begin(), indices.end(), 
        [&thread_maps, &texts] (size_t index) {

            auto& text = texts[index];
            auto& local_map = thread_maps[index];

            for (auto c : text) {
                if (std::isalpha(c)) {
                    local_map[tolower(c)]++;
            }


        }
    });

    // merge

    std::unordered_map<char, int> out;

    for (const auto& map : thread_maps) {

        for (const auto& [ch, count] : map) {

            out[ch] += count;

        }

    }

    
    return out;




}


}
