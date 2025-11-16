#include "secret_handshake.h"
#include <algorithm>
#include <array>

namespace secret_handshake {
static constexpr std::array<const char *, 4> actions{"wink", "double blink",
                                                     "close your eyes", "jump"};
std::vector<std::string> commands(unsigned int code) {
  std::vector<std::string> selected_actions;
  selected_actions.reserve(4);
  
  for (int i = 0; i < 4; ++i) {
    if (code & (1 << i)) selected_actions.emplace_back(actions[i]);
  }
  
  if (code & 16)
    std::reverse(selected_actions.begin(), selected_actions.end());
  
  return selected_actions;
}
}  // namespace secret_handshake