import java.util.List;
import java.util.ArrayList;

public class Sieve {
    private boolean[] sieve;

    public Sieve(int limit) {
        sieve = new boolean[limit + 1];
    }

    public List<Integer> getPrimes() {
        List<Integer> primes = new ArrayList<>();
        if (sieve.length > 2) primes.add(2);
        int sqrtLimit = (int) Math.sqrt(sieve.length - 1);
        for (int i = 3; i < sieve.length; i += 2) {
            if (!sieve[i]) {
                primes.add(i);
                if (i <= sqrtLimit) {
                    for (int m = i * i; m < sieve.length; m += i * 2) {
                        sieve[m] = true;
                    }
                }
            }
        }
        return primes;
    }
}