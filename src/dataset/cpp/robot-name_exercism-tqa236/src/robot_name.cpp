#include "robot_name.h"
#include <algorithm>
#include <random>
#include <unordered_set>

namespace robot_name {
static std::unordered_set<std::string> used_names;

auto& prng() {
  static std::mt19937 engine{std::random_device{}()};
  return engine;
}

char random_uppercase() {
  auto& engine = prng();
  std::uniform_int_distribution<> distrib('A', 'Z');
  return distrib(engine);
}
char random_digit() {
  auto& engine = prng();
  std::uniform_int_distribution<> distrib('0', '9');
  return distrib(engine);
}

std::string gen_name() {
  std::string name_ = {random_uppercase(), random_uppercase(), random_digit(),
                       random_digit(), random_digit()};
  return name_;
}

robot::robot() { reset(); }

std::string robot::name() const& { return name_; }

void robot::reset() {
  unsigned int size = used_names.size();
  do {
    name_ = gen_name();
    used_names.insert(name_);
  } while (used_names.size() != size + 1);
}
}  // namespace robot_name
