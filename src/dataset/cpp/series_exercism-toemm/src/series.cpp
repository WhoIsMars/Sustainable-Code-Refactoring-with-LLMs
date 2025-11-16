#include "series.h"

#include <vector>
#include <string>
#include <stdexcept>
namespace series {

using namespace std;

const vector<string> slice(const string& str, int i) {

    int str_size = str.size();

    if (i <= 0 || i > str_size) throw std::domain_error("Invalid.");
    
    vector<string> out{};
    
    for (int j{}; j <= str_size-i; j++) {
        out.push_back(str.substr(j, i));
    }


    return out;


}


// TODO: add your solution here

}  // namespace series
