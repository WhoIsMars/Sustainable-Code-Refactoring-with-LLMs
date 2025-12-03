import java.util.List;
import java.util.ArrayList;

class Sieve {
    private final int maxPrime;
    private final boolean[] isPrime;
            
    Sieve(int maxPrime) {
        this.maxPrime = maxPrime;
        this.isPrime = new boolean[maxPrime + 1];
        for (int i = 2; i <= maxPrime; i++) {
            isPrime[i] = true;
        }
    }

    List<Integer> getPrimes() {
        for (int i = 2; i * i <= maxPrime; i++) {
            if (isPrime[i]) {
                for (int j = i * i; j <= maxPrime; j += i) {
                    isPrime[j] = false;
                }
            }
        }
        
        List<Integer> primes = new ArrayList<>();
        for (int i = 2; i <= maxPrime; i++) {
            if (isPrime[i]) {
                primes.add(i);
            }
        }
        
        return primes;
    }
}