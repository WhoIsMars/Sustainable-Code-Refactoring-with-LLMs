#include "series.h"

#include <vector>
#include <string>
#include <stdexcept>
namespace series {

using namespace std;

const vector<string> slice(const string& str, int i) {

    const int str_size = str.size();

    if (i <= 0 || i > str_size) throw std::domain_error("Invalid.");
    
    vector<string> out;
    out.reserve(str_size - i + 1);
    
    for (int j = 0; j <= str_size - i; ++j) {
        out.emplace_back(str, j, i);
    }

    return out;
}

}  // namespace series