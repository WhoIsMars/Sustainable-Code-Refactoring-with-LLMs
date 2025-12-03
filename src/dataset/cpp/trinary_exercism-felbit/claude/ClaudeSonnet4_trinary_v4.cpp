#include "trinary.h"

namespace trinary
{

    int to_decimal(const std::string _trinary)
    {
        if (_trinary.empty()) {
            return 0;
        }
        
        int _decimal = 0;
        int _multiplier = 1;
        
        for (auto it = _trinary.rbegin(); it != _trinary.rend(); ++it) {
            char digit = *it;
            if (digit < '0' || digit > '2') {
                return 0;
            }
            
            _decimal += (digit - '0') * _multiplier;
            _multiplier *= 3;
        }
        
        return _decimal;
    }

} // namespace trinary