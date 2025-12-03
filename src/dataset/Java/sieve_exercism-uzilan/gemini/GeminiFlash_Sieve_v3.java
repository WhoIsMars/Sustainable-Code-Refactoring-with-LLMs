import java.util.ArrayList;
import java.util.List;

class Sieve {

    private final int maxPrime;
    private final boolean[] isPrime;
    private final List<Integer> primes;

    Sieve(int maxPrime) {
        this.maxPrime = maxPrime;
        this.isPrime = new boolean[maxPrime + 1];
        this.primes = new ArrayList<>();

        createSieve();
        populatePrimesList();
    }

    List<Integer> getPrimes() {
        return primes;
    }

    private void createSieve() {
        // Initialize all numbers as prime
        for (int i = 2; i <= maxPrime; i++) {
            isPrime[i] = true;
        }

        // Sieve of Eratosthenes
        for (int p = 2; p * p <= maxPrime; p++) {
            // If isPrime[p] is not changed, then it is a prime
            if (isPrime[p]) {
                // Update all multiples of p
                for (int i = p * p; i <= maxPrime; i += p) {
                    isPrime[i] = false;
                }
            }
        }
    }

    private void populatePrimesList() {
        for (int p = 2; p <= maxPrime; p++) {
            if (isPrime[p]) {
                primes.add(p);
            }
        }
    }

    private List<MaybePrime> createListWithMaybePrimes() {
        List<MaybePrime> maybePrimes = new ArrayList<>();
        for (int i = 2; i <= maxPrime; i++) {
            maybePrimes.add(new MaybePrime(i));
        }
        return maybePrimes;
    }

    private void markAllPrimeMultiplesNonPrime() {
        List<MaybePrime> maybePrimes = createListWithMaybePrimes();
        for (MaybePrime maybePrime : maybePrimes) {
            if (maybePrime.isPrime) {
                for (int i = maybePrime.number * maybePrime.number; i <= maxPrime; i += maybePrime.number) {
                    markNonPrime(i);
                }
            }
        }
    }

    private void markNonPrime(Integer multiple) {
        List<MaybePrime> maybePrimes = createListWithMaybePrimes();
        for (MaybePrime maybePrime : maybePrimes) {
            if (maybePrime.number == multiple) {
                maybePrime.isPrime = false;
                break;
            }
        }
    }

    class MaybePrime {

        private int number;
        private boolean isPrime = true;

        MaybePrime(int number) {
            this.number = number;
        }
    }
}