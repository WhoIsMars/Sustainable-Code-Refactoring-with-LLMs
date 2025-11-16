#include "leap.h"

namespace leap {
    /*  Naive Way
    bool is_leap_year(int year) {
        if (year % 4 == 0) {
            if (year % 100 == 0) {
                if (year % 400 == 0) {
                    return true;
                }
                return false;
            }
            return true;
        }
        return false;
    }
    */

    /* Weird
    bool is_leap_year( int year ) {
      bool result = false;

      int mod4 = ( year % 4 == 0 ) * 100;
      int mod100 = ( year % 100 == 0 ) * 10;
      int mod400 = ( year % 400 == 0 ) * 1;

      switch ( mod4 + mod100 + mod400 ) {
        case 0 : break;
        case 100 : result = true;
        case 110 : break;
        case 111 : result = true;
      }
      return result;
    }
    */

  // Took-me-forever-but-very-cool Way
  bool is_leap_year( int year ) {
    return ( 
      ( year % 4 == 0 ) && 
      ( ( year % 100 != 0 ) || ( year % 400 == 0 ) ) );
  }


}  // namespace leap
