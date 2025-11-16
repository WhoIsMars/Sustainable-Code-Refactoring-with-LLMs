#include "kindergarten_garden.h"

#include <stdexcept>

using std::array;
using std::string;

array<kindergarten_garden::Plants, 4> 
kindergarten_garden::plants(string const& garden, string const& student) {

    const size_t upRowIdx = 2 * (student[0] - 'A');
    const size_t dnRowIdx = garden.find('\n') + upRowIdx + 1;
    
    return {
        static_cast<Plants>(garden[upRowIdx]),
        static_cast<Plants>(garden[upRowIdx + 1]),
        static_cast<Plants>(garden[dnRowIdx]),
        static_cast<Plants>(garden[dnRowIdx + 1])
    };
}