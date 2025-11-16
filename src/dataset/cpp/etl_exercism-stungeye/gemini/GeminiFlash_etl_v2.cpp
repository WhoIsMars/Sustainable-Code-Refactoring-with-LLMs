#include "etl.h"

#include <algorithm>
#include <cctype>
#include <unordered_map>

namespace etl {

    modern_score_map transform(const legacy_score_map& old_points) {
        modern_score_map output;
        output.reserve(old_points.size() * 5); // Average letters per value

        for (const auto& [value, letters] : old_points) {
            for (char letter : letters) {
                output[static_cast<char>(std::tolower(letter))] = value;
            }
        }

        return output;
    }
} // namespace etl