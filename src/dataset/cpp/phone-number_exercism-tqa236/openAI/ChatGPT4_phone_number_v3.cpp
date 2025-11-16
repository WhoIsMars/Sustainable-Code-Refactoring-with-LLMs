#include "phone_number.h"
#include <stdexcept>

using std::domain_error;
using std::string;

namespace phone_number {

string phone_number::valid_phone_number() {
  size_t len = only_number.length();
  if (len < 10 || len > 11 || (len == 11 && only_number.front() != '1') ||
      only_number[len - 10] < '2' || only_number[len - 7] < '2') {
    throw domain_error("Invalid number.");
  }
  return only_number.substr(len - 10);
}

phone_number::operator string() const {
  return "(" + area_code() + ") " + only_number.substr(3, 3) + "-" + only_number.substr(6, 4);
}

}  // namespace phone_number