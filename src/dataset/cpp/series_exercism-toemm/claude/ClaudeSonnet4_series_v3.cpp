#include "series.h"

#include <vector>
#include <string>
#include <stdexcept>

namespace series {

const std::vector<std::string> slice(const std::string& str, int i) {
    const int str_size = static_cast<int>(str.size());
    
    if (i <= 0 || i > str_size) {
        throw std::domain_error("Invalid.");
    }
    
    const int result_size = str_size - i + 1;
    std::vector<std::string> out;
    out.reserve(result_size);
    
    for (int j = 0; j < result_size; ++j) {
        out.emplace_back(str, j, i);
    }
    
    return out;
}

}  // namespace series