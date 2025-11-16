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
  
  const size_t area_code_idx = len - 10;
  const size_t exchange_idx = len - 7;
  
  if ((only_number[area_code_idx] - '0') < 2) {
    throw domain_error("Invalid number.");
  }
  
  if ((only_number[exchange_idx] - '0') < 2) {
    throw domain_error("Invalid number.");
  }
  
  return only_number.substr(area_code_idx);
}

phone_number::operator string() const {
  const string& area = area_code();
  string pretty_number;
  pretty_number.reserve(14); // "(" + 3 + ") " + 3 + "-" + 4
  
  pretty_number += '(';
  pretty_number += area;
  pretty_number += ") ";
  pretty_number += only_number.substr(3, 3);
  pretty_number += '-';
  pretty_number += only_number.substr(6, 4);
  
  return pretty_number;
}

}  // namespace phone_number