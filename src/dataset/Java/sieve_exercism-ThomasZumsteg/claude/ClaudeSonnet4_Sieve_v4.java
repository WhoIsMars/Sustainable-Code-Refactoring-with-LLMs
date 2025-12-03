import java.util.List;
import java.util.ArrayList;

public class Sieve {
    private boolean[] sieve;

    public Sieve(int limit) {
        sieve = new boolean[limit + 1];
        if (limit >= 2) {
            sieve[0] = sieve[1] = true;
            for (int i = 4; i < sieve.length; i += 2) {
                sieve[i] = true;
            }
            
            int sqrtLimit = (int) Math.sqrt(limit);
            for (int i = 3; i <= sqrtLimit; i += 2) {
                if (!sieve[i]) {
                    for (int m = i * i; m < sieve.length; m += 2 * i) {
                        sieve[m] = true;
                    }
                }
            }
        }
    }

    public List<Integer> getPrimes() {
        List<Integer> primes = new ArrayList<>();
        if (sieve.length > 2) {
            primes.add(2);
            for (int i = 3; i < sieve.length; i += 2) {
                if (!sieve[i]) {
                    primes.add(i);
                }
            }
        }
        return primes;
    }
}