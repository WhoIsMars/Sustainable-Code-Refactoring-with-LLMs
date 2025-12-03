#include "two_fer.h"

namespace two_fer {

string two_fer(string str) {
    string result;
    result.reserve(str.size() + 19);
    result += "One for ";
    result += str;
    result += ", one for me.";
    return result;
}

} // namespace two_fer