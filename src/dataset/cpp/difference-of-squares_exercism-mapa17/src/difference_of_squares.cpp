#include "difference_of_squares.h"
#include <iostream>

namespace squares{
    long square_of_sums(long N){
        if(N < 2)
            return 0;

        // If N is odd, work with (N-1) and add N at the end
        long add = 0;
        if(N % 2 == 1){
            add = N;
            N = N - 1;
        }

        long sum = ((N/2) * (N+1)) + add;
        return sum*sum;
    }

    long sum_of_squares(long N){
        long sum = N*N;
        long diff = (2*N)-1;

        long NN = N*N;
        while(diff > 1){
            NN = NN - diff;
            sum += NN;
            diff -= 2;
        }
        return sum;
    }

    long difference(long N)
    {
        return square_of_sums(N) - sum_of_squares(N);
    }
}