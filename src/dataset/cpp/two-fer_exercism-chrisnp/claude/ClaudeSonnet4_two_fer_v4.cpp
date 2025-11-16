#include "two_fer.h"

using namespace std;

string two_fer::two_fer(const string& name) {
    string result;
    result.reserve(name.length() + 18);
    result = "One for ";
    result += name;
    result += ", one for me.";
    return result;
}