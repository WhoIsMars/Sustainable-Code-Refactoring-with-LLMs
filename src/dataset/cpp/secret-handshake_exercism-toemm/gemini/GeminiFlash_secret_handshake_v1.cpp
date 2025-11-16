#include "secret_handshake.h"

#include <vector>
#include <algorithm>

namespace secret_handshake {

std::vector<std::string> commands(int i) {
    std::vector<std::string> secret_commands;
    secret_commands.reserve(4); // Maximum possible size

    if (i & 1) {
        secret_commands.emplace_back("wink");
    }
    if (i & 2) {
        secret_commands.emplace_back("double blink");
    }
    if (i & 4) {
        secret_commands.emplace_back("close your eyes");
    }
    if (i & 8) {
        secret_commands.emplace_back("jump");
    }

    if (i & 16) {
        std::reverse(secret_commands.begin(), secret_commands.end());
    }

    return secret_commands;
}

}  // namespace secret_handshake