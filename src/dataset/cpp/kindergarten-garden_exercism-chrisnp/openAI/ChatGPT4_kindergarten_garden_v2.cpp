#include "kindergarten_garden.h"

#include <stdexcept>
#include <array>

using std::array;
using std::string;
using luint = long unsigned int;

array<kindergarten_garden::Plants, 4> 
kindergarten_garden::plants(string const& garden, string const& student) {
    const luint studentIdx = student.at(0) - 'A';
    const luint rowLength = garden.find('\n');
    const luint upRowIdx = 2 * studentIdx;
    const luint dnRowIdx = rowLength + upRowIdx + 1;

    return {
        static_cast<Plants>(garden[upRowIdx]),
        static_cast<Plants>(garden[upRowIdx + 1]),
        static_cast<Plants>(garden[dnRowIdx]),
        static_cast<Plants>(garden[dnRowIdx + 1])
    };
}