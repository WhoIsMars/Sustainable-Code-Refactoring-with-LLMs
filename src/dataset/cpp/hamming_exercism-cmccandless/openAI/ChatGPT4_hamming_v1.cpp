#include <stdexcept>
#include "hamming.h"

using namespace std;

int hamming::compute(const string& a, const string& b)
{
    if (a.size() != b.size())
    {
        throw domain_error("a.size() != b.size()");
    }

    int result = 0;
    for (size_t i = 0, n = a.size(); i < n; ++i)
    {
        if (a[i] != b[i])
        {
            ++result;
        }
    }
    return result;
}