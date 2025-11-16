#include <stdexcept>
#include "hamming.h"

int hamming::compute(const std::string& a, const std::string& b)
{
    if (a.size() != b.size())
    {
        throw std::domain_error("a.size() != b.size()");
    }

    return std::transform_reduce(a.begin(), a.end(), b.begin(), 0, std::plus<>(), std::not_equal_to<>());
}