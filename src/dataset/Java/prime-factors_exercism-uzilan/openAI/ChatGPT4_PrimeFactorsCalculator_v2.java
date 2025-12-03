import java.util.ArrayList;
import java.util.List;

public class PrimeFactorsCalculator {

    public List<Long> calculatePrimeFactorsOf(long number) {
        List<Long> primeFactors = new ArrayList<>();
        for (long i = 2; i * i <= number; i++) {
            while (number % i == 0) {
                primeFactors.add(i);
                number /= i;
            }
        }
        if (number > 1) {
            primeFactors.add(number);
        }
        return primeFactors;
    }
}