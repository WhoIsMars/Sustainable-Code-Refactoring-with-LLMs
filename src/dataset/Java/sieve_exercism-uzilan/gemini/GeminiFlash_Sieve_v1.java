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

        // Initialize all numbers as potentially prime
        for (int i = 2; i <= maxPrime; i++) {
            isPrime[i] = true;
        }

        markAllPrimeMultiplesNonPrime();

        // Collect the prime numbers
        for (int i = 2; i <= maxPrime; i++) {
            if (isPrime[i]) {
                primes.add(i);
            }
        }
    }

    List<Integer> getPrimes() {
        return primes;
    }

    private void markAllPrimeMultiplesNonPrime() {
        for (int p = 2; p * p <= maxPrime; p++) {
            // If isPrime[p] is not changed, then it is a prime
            if (isPrime[p]) {
                // Update all multiples of p, starting from p*p
                for (int i = p * p; i <= maxPrime; i += p) {
                    isPrime[i] = false;
                }
            }
        }
    }
}