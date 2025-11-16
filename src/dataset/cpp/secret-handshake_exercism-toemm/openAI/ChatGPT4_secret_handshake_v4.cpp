#include "secret_handshake.h"
#include <vector>
#include <string>

namespace secret_handshake {

std::vector<std::string> commands(int i) {
    static const std::vector<std::string> actions{"wink", "double blink", "close your eyes", "jump"};
    std::vector<std::string> secret_commands;
    secret_commands.reserve(4);

    for (int k = 0; k < 4; ++k) {
        if (i & (1 << k)) secret_commands.push_back(actions[k]);
    }

    if (i & 16) {
        std::reverse(secret_commands.begin(), secret_commands.end());
    }

    return secret_commands;
}

}  // namespace secret_handshake