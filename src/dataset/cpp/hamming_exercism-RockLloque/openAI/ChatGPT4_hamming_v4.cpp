#include "hamming.h"
#include <stdexcept>
#include <string>

int hamming::compute(const std::string& genecode1, const std::string& genecode2)
{
    if (genecode1.size() != genecode2.size())
        throw std::domain_error("");

    int counter = 0;
    for (size_t i = 0, n = genecode1.size(); i < n; ++i)
    {
        counter += (genecode1[i] != genecode2[i]);
    }
    return counter;
}