#include "clock.h"

#include <string>
#include <array>

namespace date_independent {

    clock::clock(int hour, int min) : _hour(0), _min(0) {
        int total_min = (hour * 60 + min) % MIN_PER_DAY;
        
        if (total_min < 0) {
            total_min += MIN_PER_DAY;
        }

        _hour = total_min / 60;
        _min = total_min % 60;
    }

    clock clock::plus(int min) const {
        return clock(_hour, _min + min);
    }
    
    clock clock::at(int hour, int min) {
        return clock{hour, min};
    }

    bool clock::operator==(const clock& rhs) const {
        return (_hour == rhs._hour) && (_min == rhs._min);
    }

    bool clock::operator!=(const clock& rhs) const {
        return (_hour != rhs._hour) || (_min != rhs._min);
    }

    clock::operator std::string() const {
        constexpr std::array<const char*, 100> two_digit_strings = {
            "00", "01", "02", "03", "04", "05", "06", "07", "08", "09",
            "10", "11", "12", "13", "14", "15", "16", "17", "18", "19",
            "20", "21", "22", "23", "24", "25", "26", "27", "28", "29",
            "30", "31", "32", "33", "34", "35", "36", "37", "38", "39",
            "40", "41", "42", "43", "44", "45", "46", "47", "48", "49",
            "50", "51", "52", "53", "54", "55", "56", "57", "58", "59",
            "60", "61", "62", "63", "64", "65", "66", "67", "68", "69",
            "70", "71", "72", "73", "74", "75", "76", "77", "78", "79",
            "80", "81", "82", "83", "84", "85", "86", "87", "88", "89",
            "90", "91", "92", "93", "94", "95", "96", "97", "98", "99"
        };
        
        std::string result;
        result.reserve(5);
        result += two_digit_strings[_hour];
        result += ':';
        result += two_digit_strings[_min];
        
        return result;
    }

}  // namespace date_independent