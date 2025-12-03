#include <stdexcept>
#include <string>
#include "hamming.h"

using namespace std;

int hamming::compute(const string& a, const string& b)
{
    if (a.size() != b.size())
    {
        throw domain_error("a.size() != b.size()");
    }

    return inner_product(a.begin(), a.end(), b.begin(), 0, plus<>(), not_equal_to<>());
}