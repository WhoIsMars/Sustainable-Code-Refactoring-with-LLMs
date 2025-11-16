#include "hamming.h"
#include <stdexcept>
#include <string>

int hamming::compute(std::string const& genecode1, std::string const& genecode2)
{
    if (genecode1.size() != genecode2.size())
        throw std::domain_error("");

    int counter = 0;
    for (size_t i = 0, n = genecode1.size(); i < n; ++i)
    {
        if (genecode1[i] != genecode2[i])
            ++counter;
    }
    return counter;
}