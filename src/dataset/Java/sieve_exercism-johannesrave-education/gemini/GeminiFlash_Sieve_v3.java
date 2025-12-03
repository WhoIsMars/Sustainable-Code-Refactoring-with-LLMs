import java.util.List;
import java.util.ArrayList;
import java.util.BitSet;

class Sieve {
    private final int maxPrime;
    private final BitSet isComposite;

    Sieve(int maxPrime) {
        this.maxPrime = maxPrime;
        this.isComposite = new BitSet(maxPrime + 1);
    }

    List<Integer> getPrimes() {
        ArrayList<Integer> primes = new ArrayList<>();
        int limit = (int) Math.sqrt(maxPrime);

        for (int p = 2; p <= limit; p++) {
            if (!isComposite.get(p)) {
                for (int i = p * p; i <= maxPrime; i += p) {
                    isComposite.set(i);
                }
            }
        }

        for (int p = 2; p <= maxPrime; p++) {
            if (!isComposite.get(p)) {
                primes.add(p);
            }
        }

        return primes;
    }
}