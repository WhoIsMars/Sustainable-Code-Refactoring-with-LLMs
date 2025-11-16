#include "etl.h"

#include <cctype>

namespace etl {

    modern_score_map transform(const legacy_score_map& old_points) {
        modern_score_map output;
        
        size_t total_letters = 0;
        for (const auto& value_to_letters : old_points) {
            total_letters += value_to_letters.second.size();
        }
        output.reserve(total_letters);

        for (const auto& value_to_letters : old_points) {
            const auto value = value_to_letters.first;
            const auto& letters = value_to_letters.second;

            for (const auto letter : letters) {
                output.emplace(std::tolower(letter), value);
            }
        }

        return output;
    }
} // namespace etl