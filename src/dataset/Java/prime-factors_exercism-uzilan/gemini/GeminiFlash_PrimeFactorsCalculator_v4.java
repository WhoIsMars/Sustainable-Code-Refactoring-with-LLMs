import java.util.ArrayList;
import java.util.List;

public class PrimeFactorsCalculator {

    public List<Long> calculatePrimeFactorsOf(long number) {
        List<Long> factors = new ArrayList<>();
        if (number <= 1) {
            return factors;
        }

        long n = number;
        for (long i = 2; i * i <= n; i++) {
            while (n % i == 0) {
                factors.add(i);
                n /= i;
            }
        }

        if (n > 1) {
            factors.add(n);
        }

        return factors;
    }
}