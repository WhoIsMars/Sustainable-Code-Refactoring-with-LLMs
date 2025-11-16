#include "secret_handshake.h"

namespace secret_handshake {

std::vector<std::string> commands(int i) {
    static const std::vector<std::string> actions{"wink", "double blink", "close your eyes", "jump"};
    std::vector<std::string> secret_commands;
    secret_commands.reserve(4);

    if (i & 16) {  // bit 4 set - reverse order
        for (int k = 3; k >= 0; --k) {
            if (i & (1 << k)) {
                secret_commands.emplace_back(actions[k]);
            }
        }
    } else {  // normal order
        for (int k = 0; k < 4; ++k) {
            if (i & (1 << k)) {
                secret_commands.emplace_back(actions[k]);
            }
        }
    }

    return secret_commands;
}

}  // namespace secret_handshake