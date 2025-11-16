#include "hamming.h"
#include <stdexcept>

int hamming::compute(std::string const& genecode1, std::string const& genecode2)
{
    if(genecode1.length() != genecode2.length())
        throw std::domain_error("");

    int counter = 0;
    const size_t length = genecode1.length();
    
    for(size_t i = 0; i < length; ++i)
    {
        if(genecode1[i] != genecode2[i]) {
            ++counter;
        }
    }
    return counter;
}