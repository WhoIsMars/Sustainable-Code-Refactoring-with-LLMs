#include "secret_handshake.h"
#include <algorithm>
#include <array>

namespace secret_handshake {
static const std::array<const char *, 4> actions{"wink", "double blink",
                                                 "close your eyes", "jump"};
std::vector<std::string> commands(unsigned int code) {
  std::vector<std::string> selected_actions;
  for (long unsigned int i = 0; i != actions.size(); i++) {
    if (code & (1 << i)) selected_actions.push_back(actions[i]);
  }
  if (code & (1 << actions.size()))
    std::reverse(selected_actions.begin(), selected_actions.end());
  return selected_actions;
}
}  // namespace secret_handshake
