#include "phone_number.h"
#include <stdexcept>

using std::domain_error;
using std::string;

namespace phone_number {

string phone_number::valid_phone_number() {
  if ((only_number.length() < 10) || (only_number.length() > 11)) {
    throw domain_error("Invalid number.");
  }
  if ((only_number.length() == 11) && (only_number.front() != '1')) {
    throw domain_error("Invalid number.");
  }
  if ((only_number.at(only_number.length() - 10) - '0') < 2) {
    throw domain_error("Invalid number.");
  }
  if ((only_number.at(only_number.length() - 7) - '0') < 2) {
    throw domain_error("Invalid number.");
  }
  return only_number.substr(only_number.length() - 10);
}
phone_number::operator string() const {
  string pretty_number = "(" + area_code() + ") " + only_number.substr(3, 3) +
                         "-" + only_number.substr(6, 4);
  return pretty_number;
}
}  // namespace phone_number
