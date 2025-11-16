#include "kindergarten_garden.h"

#include <stdexcept>
#include <algorithm>

using std::array;
using std::string;
using luint = long unsigned int;

array<kindergarten_garden::Plants, 4> 
kindergarten_garden::plants(string const& garden, string const& student) {
    luint upRowIdx = 2u * (student[0] - 'A');
    luint dnRowIdx = garden.find('\n') + upRowIdx + 1;

    return {
        static_cast<Plants>(garden[upRowIdx]),
        static_cast<Plants>(garden[upRowIdx + 1]),
        static_cast<Plants>(garden[dnRowIdx]),
        static_cast<Plants>(garden[dnRowIdx + 1])
    };
}