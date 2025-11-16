#include "reverse_string.h"

namespace reverse_string {

    std::string reverse_string(std::string input) {
        std::string reverse_input = "";

        for (std::string::reverse_iterator position = input.rbegin(); position != input.rend(); ++position)
            reverse_input = reverse_input + *position;

        return reverse_input;
    }

}  // namespace reverse_string
