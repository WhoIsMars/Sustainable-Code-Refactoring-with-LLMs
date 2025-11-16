#include "two_fer.h"

using namespace std;

string two_fer::two_fer(const string& name) {
    string result;
    result.reserve(8 + name.length() + 13); // "One for " + name + ", one for me."
    result += "One for ";
    result += name;
    result += ", one for me.";
    return result;
}