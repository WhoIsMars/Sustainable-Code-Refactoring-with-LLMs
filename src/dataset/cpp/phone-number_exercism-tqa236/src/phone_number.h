#pragma once
#include <string>

using std::string;

namespace phone_number {

class phone_number {
 private:
  string only_number = "";

 public:
  phone_number(string number) {
    for (char& c : number) {
      if ((c >= '0') && (c <= '9')) {
        only_number = only_number + c;
      }
    }
    only_number = valid_phone_number();
  }
  string valid_phone_number();
  string number() const { return only_number; }
  string area_code() const {
    return only_number.substr(only_number.length() - 10, 3);
  };
  operator string() const;
};
}  // namespace phone_number
