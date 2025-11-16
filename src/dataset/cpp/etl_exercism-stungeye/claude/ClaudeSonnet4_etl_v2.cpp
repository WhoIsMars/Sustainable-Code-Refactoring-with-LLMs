#include "etl.h"

#include <cctype>

namespace etl {

    modern_score_map transform(const legacy_score_map& old_points) {
        modern_score_map output;
        output.reserve(26); // Reserve space for all letters

        for (const auto& value_to_letters : old_points) {
            const auto value = value_to_letters.first;
            const auto& letters = value_to_letters.second;

            for (const auto letter : letters) {
                output[std::tolower(static_cast<unsigned char>(letter))] = value;
            }
        }

        return output;
    }
} // namespace etl