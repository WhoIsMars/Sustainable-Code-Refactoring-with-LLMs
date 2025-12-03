#include "raindrops.h"
#include <string>

using namespace std;

namespace raindrops
{
    string convert(int n)
    {
        string result;
        result.reserve(16);

        if (n % 3 == 0)
        {
            result += "Pling";
        }

        if (n % 5 == 0)
        {
            result += "Plang";
        }

        if (n % 7 == 0)
        {
            result += "Plong";
        }

        if (result.empty())
        {
            result = std::to_string(n);
        }

        return result;
    }
}