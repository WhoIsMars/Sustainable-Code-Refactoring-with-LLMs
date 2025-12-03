import java.util.ArrayList;
import java.util.List;

import static java.util.Collections.emptyList;

public class PrimeFactorsCalculator {

    public List<Long> calculatePrimeFactorsOf(long number) {
        if (number <= 1) {
            return emptyList();
        }
        
        List<Long> factors = new ArrayList<>();
        
        while (number % 2 == 0) {
            factors.add(2L);
            number /= 2;
        }
        
        for (long i = 3; i * i <= number; i += 2) {
            while (number % i == 0) {
                factors.add(i);
                number /= i;
            }
        }
        
        if (number > 2) {
            factors.add(number);
        }
        
        return factors;
    }
}