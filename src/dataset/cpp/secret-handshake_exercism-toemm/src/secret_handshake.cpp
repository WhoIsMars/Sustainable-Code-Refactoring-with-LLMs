#include "secret_handshake.h"

#include <cmath>
#include <algorithm>

namespace secret_handshake {

std::vector<std::string> commands(int i) {

    std::vector<std::string> actions{"wink", "double blink", "close your eyes", "jump"};
    std::vector<std::string> secret_commands{};

    // i=9   0 1 0 0 1
    for (int k = 0; k < 4; k++) {
        if (i & (1 << k)) secret_commands.emplace_back(actions[k]);
    }

    if (i & (1 << 4)) {
       std::reverse(secret_commands.begin(), secret_commands.end()); 
    } 

    return secret_commands;

}

}  // namespace secret_handshake
