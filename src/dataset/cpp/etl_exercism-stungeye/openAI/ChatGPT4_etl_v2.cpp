#include "etl.h"

#include <cctype>
#include <unordered_map>

namespace etl {

    modern_score_map transform(const legacy_score_map& old_points) {
        modern_score_map output;
        output.reserve(old_points.size()); // Reserve space to reduce reallocations

        for (const auto& [value, letters] : old_points) {
            for (char letter : letters) {
                output.emplace(std::tolower(letter), value);
            }
        }

        return output;
    }
} // namespace etl