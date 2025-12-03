import java.util.ArrayList;
import java.util.List;

public class PrimeFactorsCalculator {

    public List<Long> calculatePrimeFactorsOf(long number) {
        List<Long> factors = new ArrayList<>();
        if (number <= 1) {
            return factors;
        }

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