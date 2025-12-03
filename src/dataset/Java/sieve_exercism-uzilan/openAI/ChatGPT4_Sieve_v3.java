import java.util.ArrayList;
import java.util.List;

class Sieve {

    private final int maxPrime;
    private final List<Integer> primes;

    Sieve(int maxPrime) {
        this.maxPrime = maxPrime;
        this.primes = calculatePrimes();
    }

    List<Integer> getPrimes() {
        return primes;
    }

    private List<Integer> calculatePrimes() {
        boolean[] isPrime = new boolean[maxPrime + 1];
        List<Integer> primes = new ArrayList<>();

        for (int i = 2; i <= maxPrime; i++) {
            isPrime[i] = true;
        }

        for (int i = 2; i * i <= maxPrime; i++) {
            if (isPrime[i]) {
                for (int j = i * i; j <= maxPrime; j += i) {
                    isPrime[j] = false;
                }
            }
        }

        for (int i = 2; i <= maxPrime; i++) {
            if (isPrime[i]) {
                primes.add(i);
            }
        }

        return primes;
    }
}