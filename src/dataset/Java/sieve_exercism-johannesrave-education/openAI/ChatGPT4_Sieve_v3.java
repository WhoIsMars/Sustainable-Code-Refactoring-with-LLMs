import java.util.List;
import java.util.ArrayList;
import java.util.BitSet;

class Sieve {
    private final int maxPrime;
    private final BitSet isPrime;

    Sieve(int maxPrime) {
        this.maxPrime = maxPrime;
        this.isPrime = new BitSet(maxPrime + 1);
        this.isPrime.set(2, maxPrime + 1);
    }

    List<Integer> getPrimes() {
        for (int i = 2; i * i <= maxPrime; i++) {
            if (isPrime.get(i)) {
                for (int j = i * i; j <= maxPrime; j += i) {
                    isPrime.clear(j);
                }
            }
        }

        List<Integer> primes = new ArrayList<>();
        for (int i = 2; i <= maxPrime; i++) {
            if (isPrime.get(i)) {
                primes.add(i);
            }
        }
        return primes;
    }
}