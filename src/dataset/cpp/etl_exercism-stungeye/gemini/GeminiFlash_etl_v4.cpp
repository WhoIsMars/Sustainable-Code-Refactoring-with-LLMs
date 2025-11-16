#include "etl.h"

#include <cctype>
#include <algorithm>

namespace etl {

    modern_score_map transform(const legacy_score_map& old_points) {
        modern_score_map output;
        output.reserve(26); // Pre-allocate space for all possible letters

        for (const auto& [value, letters] : old_points) {
            for (char letter : letters) {
                output[std::tolower(letter)] = value;
            }
        }

        return output;
    }
} // namespace etl