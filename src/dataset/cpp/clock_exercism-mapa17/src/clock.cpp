#include "clock.h"
#include <boost/format.hpp>
#include <sstream>

namespace date_independent {
    using namespace std;
    using namespace boost;

    clock::clock(const int hour, const int minute){
        #define cx_minperday 60*24
        
        time_in_minutes = hour*60 + minute;
        time_in_minutes %= cx_minperday;
        if(time_in_minutes < 0)
            time_in_minutes += cx_minperday; 
    }

    clock clock::at(const int hour, const int minute){
        return clock(hour, minute);
    }

    clock clock::plus(int minute){
        return clock(0, time_in_minutes + minute);
    }

    clock::operator std::string() const {
        stringstream stream;
        stream << format("%02d:%02d") % int(time_in_minutes/60) % (time_in_minutes%60);
        return stream.str();
    }
}  // namespace date_independent
