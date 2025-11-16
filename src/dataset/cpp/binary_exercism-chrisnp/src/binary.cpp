#include "binary.h"
#include <cmath>

using std::string;

long binary::convert (const string& binstr) noexcept {
    for ( auto&& d: binstr ) if ( !isdigit(d) ) return 0;
    
    auto binary { stoll(binstr, static_cast<size_t>(0), 10) }; 
    long decimal { 0 }, position { 0 };
    
    while ( binary != 0 ) {
        decimal += (binary % 10) * pow(2, position);
        position++;
        binary /= 10;
    }
    return decimal;
}
