#include "reverse_string.h"
#include <string>
#include <iostream>

namespace reverse_string {

    std::string reverse_string(std::string str) {

        std::string reverse_string{};

        for (int i = str.size() - 1; i >= 0; --i) {

            reverse_string += str[i];

        }
        return reverse_string;
    }


}  // namespace reverse_string
