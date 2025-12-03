#include "two_fer.h"

namespace two_fer {

string two_fer(const string& str) { 
    string result;
    result.reserve(16 + str.size()); // Pre-allocate memory
    result += "One for ";
    result += str;
    result += ", one for me.";
    return result;
}

} // namespace two_fer