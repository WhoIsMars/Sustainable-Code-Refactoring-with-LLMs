#include "hamming.h"
#include <stdexcept>
#include <string>

int hamming::compute(const std::string& genecode1, const std::string& genecode2)
{
    if (genecode1.length() != genecode2.length())
        throw std::domain_error("");

    int counter = 0;
    for (size_t i = 0, n = genecode1.length(); i < n; ++i)
    {
        if (genecode1[i] != genecode2[i])
            ++counter;
    }
    return counter;
}