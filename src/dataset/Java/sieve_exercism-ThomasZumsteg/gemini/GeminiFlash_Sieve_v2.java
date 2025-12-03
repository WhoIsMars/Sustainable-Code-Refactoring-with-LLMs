import java.util.List;
import java.util.ArrayList;
import java.util.Arrays;

public class Sieve {
    private boolean[] sieve;
    private int limit;

    public Sieve(int limit) {
        this.limit = limit;
        sieve = new boolean[limit + 1];
    }

    public List<Integer> getPrimes() {
        if (limit < 2) {
            return new ArrayList<>();
        }

        Arrays.fill(sieve, false);
        List<Integer> primes = new ArrayList<>();
        primes.add(2);

        int sqrtLimit = (int) Math.sqrt(limit);

        for (int i = 3; i <= sqrtLimit; i += 2) {
            if (!sieve[i]) {
                for (int j = i * i; j <= limit; j += 2 * i) {
                    sieve[j] = true;
                }
            }
        }

        for (int i = 3; i <= limit; i += 2) {
            if (!sieve[i]) {
                primes.add(i);
            }
        }

        return primes;
    }
}