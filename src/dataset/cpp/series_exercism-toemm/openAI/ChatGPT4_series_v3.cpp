#include "series.h"

#include <vector>
#include <string>
#include <stdexcept>
namespace series {

using namespace std;

const vector<string> slice(const string& str, int i) {
    if (i <= 0 || i > static_cast<int>(str.size())) {
        throw std::domain_error("Invalid.");
    }

    vector<string> out;
    out.reserve(str.size() - i + 1);

    for (size_t j = 0; j <= str.size() - i; ++j) {
        out.emplace_back(str, j, i);
    }

    return out;
}

}  // namespace series