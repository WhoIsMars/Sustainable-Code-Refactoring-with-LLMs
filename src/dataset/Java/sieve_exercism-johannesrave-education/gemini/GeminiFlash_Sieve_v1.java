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

        for (int i = 2; i <= limit; i++) {
            if (!isComposite.get(i)) {
                for (int j = i * i; j <= maxPrime; j += i) {
                    isComposite.set(j);
                }
            }
        }

        for (int i = 2; i <= maxPrime; i++) {
            if (!isComposite.get(i)) {
                primes.add(i);
            }
        }

        return primes;
    }
}