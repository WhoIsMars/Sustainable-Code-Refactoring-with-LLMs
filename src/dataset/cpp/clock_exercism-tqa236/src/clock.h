#pragma once
#include <iomanip>
#include <sstream>
#include <string>

namespace date_independent {
using std::ostringstream;
using std::setfill;
using std::setw;
using std::string;

class clock {
 private:
  int hour;
  int minute;

 public:
  clock(int hour, int minute) {
    this->hour = hour;
    this->minute = minute;
  }
  static clock at(int, int);
  clock plus(int);
  explicit operator string() const {
    ostringstream stream;
    stream << setfill('0') << setw(2) << hour << ':' << setw(2) << minute;
    return stream.str();
  }

  bool operator==(const clock &c) const {
    return (c.hour == hour && c.minute == minute);
  }
  bool operator!=(const clock &c) const { return !(*this == c); }
};
}  // namespace date_independent
