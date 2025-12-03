import java.util.ArrayList;
import java.util.List;

import static java.util.Collections.emptyList;

public class PrimeFactorsCalculator {

    public List<Long> calculatePrimeFactorsOf(long number) {
        if (number <= 1) {
            return emptyList();
        }
        
        List<Long> factors = new ArrayList<>();
        
        // Handle factor 2 separately to avoid even number checks
        while (number % 2 == 0) {
            factors.add(2L);
            number /= 2;
        }
        
        // Check odd factors from 3 up to sqrt(number)
        for (long i = 3; i * i <= number; i += 2) {
            while (number % i == 0) {
                factors.add(i);
                number /= i;
            }
        }
        
        // If number is still > 1, then it's a prime factor
        if (number > 1) {
            factors.add(number);
        }
        
        return factors;
    }
}