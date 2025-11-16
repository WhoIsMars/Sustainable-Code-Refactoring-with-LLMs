#include "secret_handshake.h"
#include <algorithm>
#include <array>

namespace secret_handshake {
static constexpr std::array<const char *, 4> actions{"wink", "double blink",
                                                     "close your eyes", "jump"};
std::vector<std::string> commands(unsigned int code) {
  std::vector<std::string> selected_actions;
  selected_actions.reserve(4);
  
  constexpr unsigned int action_mask = 0xF;
  const unsigned int filtered_code = code & action_mask;
  
  for (unsigned int i = 0; i < 4; ++i) {
    if (filtered_code & (1u << i)) {
      selected_actions.emplace_back(actions[i]);
    }
  }
  
  if (code & 16u) {
    std::reverse(selected_actions.begin(), selected_actions.end());
  }
  
  return selected_actions;
}
}