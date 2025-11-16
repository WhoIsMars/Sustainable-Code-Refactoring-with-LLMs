#include "secret_handshake.h"
#include <array>
#include <vector>
#include <string>

namespace secret_handshake {
constexpr std::array<const char *, 4> actions{"wink", "double blink",
                                              "close your eyes", "jump"};

std::vector<std::string> commands(unsigned int code) {
  std::vector<std::string> selected_actions;
  selected_actions.reserve(actions.size()); // Reserve memory to avoid reallocations
  for (size_t i = 0; i < actions.size(); ++i) {
    if (code & (1u << i)) selected_actions.emplace_back(actions[i]);
  }
  if (code & (1u << actions.size())) {
    std::reverse(selected_actions.begin(), selected_actions.end());
  }
  return selected_actions;
}
}  // namespace secret_handshake