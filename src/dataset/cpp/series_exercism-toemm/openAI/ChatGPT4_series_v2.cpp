#include "series.h"

#include <vector>
#include <string>
#include <stdexcept>
namespace series {

using namespace std;

vector<string> slice(const string& str, int i) {
    if (i <= 0 || i > static_cast<int>(str.size())) {
        throw std::domain_error("Invalid.");
    }

    vector<string> out;
    out.reserve(str.size() - i + 1); // Reserve memory to avoid reallocations

    for (size_t j = 0; j <= str.size() - i; ++j) {
        out.emplace_back(str, j, i); // Use emplace_back to construct directly in place
    }

    return out;
}

}  // namespace series