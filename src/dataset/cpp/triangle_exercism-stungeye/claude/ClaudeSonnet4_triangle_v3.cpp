#include "triangle.h"

namespace triangle {
  flavor kind(double a, double b, double c) {
    if ((a <= 0) || (b <= 0) || (c <= 0)) {
      throw std::domain_error("All triangle sides must have a length greater than zero.");
    }

    const double sum_ab = a + b;
    const double sum_ac = a + c;
    const double sum_bc = b + c;
    
    if ((sum_ab <= c) || (sum_ac <= b) || (sum_bc <= a)) { 
      throw std::domain_error("Combined length of any two triangle sides much be greater or equal to length of third side.");
    }

    const bool ab_equal = (a == b);
    const bool bc_equal = (b == c);
    const bool ac_equal = (a == c);
    
    if (ab_equal && bc_equal) {
      return flavor::equilateral;
    }
    
    if (ab_equal || bc_equal || ac_equal) {
      return flavor::isosceles;
    }

    return flavor::scalene;
  }
}