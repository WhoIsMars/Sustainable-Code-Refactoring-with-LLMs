#include "kindergarten_garden.h"

#include <stdexcept>
#include <algorithm>

using std::array;
using std::string;
using luint = long unsigned int;

array<kindergarten_garden::Plants, 4> 
kindergarten_garden::plants(string const& garden, string const& student) {

    const luint upRowIdx { 2u * (student.at(0) - 'A') };
    const luint dnRowIdx { garden.find('\n') + upRowIdx + 1 };
    const array<char, 4> cups {
        garden[upRowIdx], garden[upRowIdx + 1],
        garden[dnRowIdx], garden[dnRowIdx + 1]
    };
    array<Plants, 4> rows {};
    std::transform(
        cups.cbegin(), cups.cend(), rows.begin(), 
        [](char p) { return static_cast<Plants>(p); }
    );
    return rows;
}
