import java.util.ArrayList;
import java.util.List;

class Sieve {

    private final int maxPrime;
    private final boolean[] isPrime;
    private final List<Integer> primes;

    Sieve(int maxPrime) {
        this.maxPrime = maxPrime;
        this.isPrime = new boolean[maxPrime + 1];
        initializePrimeArray();
        sieveOfEratosthenes();
        this.primes = collectPrimes();
    }

    List<Integer> getPrimes() {
        return primes;
    }

    private void initializePrimeArray() {
        for (int i = 2; i <= maxPrime; i++) {
            isPrime[i] = true;
        }
    }

    private void sieveOfEratosthenes() {
        int limit = (int) Math.sqrt(maxPrime);
        for (int i = 2; i <= limit; i++) {
            if (isPrime[i]) {
                for (int j = i * i; j <= maxPrime; j += i) {
                    isPrime[j] = false;
                }
            }
        }
    }

    private List<Integer> collectPrimes() {
        List<Integer> result = new ArrayList<>();
        for (int i = 2; i <= maxPrime; i++) {
            if (isPrime[i]) {
                result.add(i);
            }
        }
        return result;
    }

    class MaybePrime {
        private int number;
        private boolean isPrime = true;

        MaybePrime(int number) {
            this.number = number;
        }
    }
}