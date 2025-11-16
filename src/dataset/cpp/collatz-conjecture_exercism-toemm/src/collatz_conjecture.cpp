#include "collatz_conjecture.h"

#include <iostream>
#include <stdexcept>

namespace collatz_conjecture {




int steps(int i) {

    int ctr{};

    //std::cout << "MAC" << std::endl;


    if (i <= 0) throw std::domain_error("i not positive and above 0");
    //std::cout << "starting with i=" << i << std::endl;

    while (i > 1) {
        
        //std::cout << "step: " << ctr+1 << ", ";
        if (!(i % 2)) i /= 2; 
        else i = i * 3 + 1;
        ctr++;
        //std::cout << i << std::endl;


    }

    return ctr;
}



}  // namespace collatz_conjecture
