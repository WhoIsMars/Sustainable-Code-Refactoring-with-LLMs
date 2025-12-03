#include "robot_name.h"
#include <iostream>
#include <random>
#include <string>

using namespace std;
using namespace robot_name;

// Static members to track used names and random number generation
static std::unordered_set<std::string> used_names;
static std::mt19937 gen(std::random_device{}());
static std::uniform_int_distribution<> letter_dist(0, 25);
static std::uniform_int_distribution<> digit_dist(0, 9);

string robot::make_name() {
  std::string new_name;
  do {
    new_name.clear();
    new_name += (char)('A' + letter_dist(gen));
    new_name += (char)('A' + letter_dist(gen));
    new_name += std::to_string(digit_dist(gen));
    new_name += std::to_string(digit_dist(gen));
    new_name += std::to_string(digit_dist(gen));
  } while (used_names.count(new_name) > 0);

  used_names.insert(new_name);
  return new_name;
}

string robot::name() const { return final_name; }

void robot::reset() {
  used_names.erase(final_name);
  final_name = make_name();
}

robot::robot() {
  final_name = make_name();
  cout << final_name << endl;
}