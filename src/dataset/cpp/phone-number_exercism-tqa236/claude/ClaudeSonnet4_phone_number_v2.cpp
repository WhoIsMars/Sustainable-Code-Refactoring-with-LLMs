#include "phone_number.h"
#include <stdexcept>

using std::domain_error;
using std::string;

namespace phone_number {

string phone_number::valid_phone_number() {
  const size_t len = only_number.length();
  if (len < 10 || len > 11) {
    throw domain_error("Invalid number.");
  }
  if (len == 11 && only_number[0] != '1') {
    throw domain_error("Invalid number.");
  }
  if ((only_number[len - 10] - '0') < 2) {
    throw domain_error("Invalid number.");
  }
  if ((only_number[len - 7] - '0') < 2) {
    throw domain_error("Invalid number.");
  }
  return only_number.substr(len - 10);
}

phone_number::operator string() const {
  string pretty_number;
  pretty_number.reserve(14); // "(xxx) xxx-xxxx" = 14 chars
  pretty_number += '(';
  pretty_number += area_code();
  pretty_number += ") ";
  pretty_number.append(only_number, 3, 3);
  pretty_number += '-';
  pretty_number.append(only_number, 6, 4);
  return pretty_number;
}
}  // namespace phone_number