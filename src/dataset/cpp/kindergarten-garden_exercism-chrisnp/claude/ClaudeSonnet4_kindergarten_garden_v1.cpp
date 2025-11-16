#include "kindergarten_garden.h"

#include <stdexcept>

using std::array;
using std::string;

array<kindergarten_garden::Plants, 4> 
kindergarten_garden::plants(string const& garden, string const& student) {

    const auto upRowIdx = static_cast<size_t>(2 * (student[0] - 'A'));
    const auto newlinePos = garden.find('\n');
    const auto dnRowIdx = newlinePos + upRowIdx + 1;
    
    return {{
        static_cast<Plants>(garden[upRowIdx]),
        static_cast<Plants>(garden[upRowIdx + 1]),
        static_cast<Plants>(garden[dnRowIdx]),
        static_cast<Plants>(garden[dnRowIdx + 1])
    }};
}