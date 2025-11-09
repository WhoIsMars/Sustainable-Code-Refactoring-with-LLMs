#include "atbash_cipher.h"
#include <string>
namespace atbash_cipher
{
    std::string encode(std::string input)
    {
        std::string output = "";
        for (int i = 0; i < input.length(); i++)
            if ((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z'))
                output.push_back('z' - (input[i] - 'a'));
            else if (input[i] >= '0' && input[i] <= '9')
                output.push_back(input[i]);

        return output;
    }
    std::string decode(std::string input)
    {
        std::string output = "";
        for (int i = 0; i < input.length(); i++)
            if ((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z'))
                output.push_back('a' + ('z' - input[i]));
            else if (input[i] >= '0' && input[i] <= '9')
                output.push_back(input[i]);

        return output;
    }
} // namespace atbash_cipher
