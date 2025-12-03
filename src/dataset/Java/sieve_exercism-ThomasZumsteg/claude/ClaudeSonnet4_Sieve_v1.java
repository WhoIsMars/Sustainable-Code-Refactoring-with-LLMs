import java.util.List;
import java.util.ArrayList;

public class Sieve {
    private boolean[] sieve;
    private final int limit;

    public Sieve(int limit) {
        this.limit = limit;
        sieve = new boolean[limit + 1];
    }

    public List<Integer> getPrimes() {
        if (limit < 2) return new ArrayList<>();
        
        // Mark even numbers as composite (except 2)
        for (int i = 4; i <= limit; i += 2) {
            sieve[i] = true;
        }
        
        // Sieve odd numbers starting from 3
        int sqrtLimit = (int) Math.sqrt(limit);
        for (int i = 3; i <= sqrtLimit; i += 2) {
            if (!sieve[i]) {
                // Start marking from i*i and increment by 2*i to skip even multiples
                for (int m = i * i; m <= limit; m += 2 * i) {
                    sieve[m] = true;
                }
            }
        }
        
        // Count primes first to optimize ArrayList capacity
        int primeCount = 0;
        if (limit >= 2) primeCount = 1; // for 2
        for (int i = 3; i <= limit; i += 2) {
            if (!sieve[i]) primeCount++;
        }
        
        // Create list with exact capacity
        List<Integer> primes = new ArrayList<>(primeCount);
        if (limit >= 2) primes.add(2);
        for (int i = 3; i <= limit; i += 2) {
            if (!sieve[i]) {
                primes.add(i);
            }
        }
        
        return primes;
    }
}