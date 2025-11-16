#include "two_fer.h"

string two_fer::two_fer(const string& name) {
    static const string suffix = ", one for me.";
    return "One for " + name + suffix;
}