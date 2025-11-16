#pragma once
#include <string>
#include <vector>

namespace robot_name {
class robot {
 private:
  std::string name_;

 public:
  robot();
  robot(const robot&) = delete;
  robot& operator=(const robot&) = delete;
  std::string name() const&;
  void reset();
};
}  // namespace robot_name
