import java.util.ArrayList;
import java.util.List;

import static java.util.Collections.emptyList;

public class PrimeFactorsCalculator {

    public List<Long> calculatePrimeFactorsOf(long number) {
        if (number <= 1) {
            return emptyList();
        }

        List<Long> factors = new ArrayList<>();
        for (long i = 2; i * i <= number; i++) {
            while (number % i == 0) {
                factors.add(i);
                number /= i;
            }
        }
        if (number > 1) {
            factors.add(number);
        }
        return factors;
    }
}