#include "raindrops.h"

namespace raindrops
{
    const char* convert(int n)
    {
        static const char* pling = "Pling";
        static const char* plang = "Plang";
        static const char* plong = "Plong";

        bool hasFactor = false;
        std::string result;

        if (n % 3 == 0)
        {
            result += pling;
            hasFactor = true;
        }

        if (n % 5 == 0)
        {
            result += plang;
            hasFactor = true;
        }

        if (n % 7 == 0)
        {
            result += plong;
            hasFactor = true;
        }

        return hasFactor ? result.c_str() : std::to_string(n).c_str();
    }
}