import java.math.BigInteger;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class DiffieHellman {

    private final Random random = new Random();

    public BigInteger privateKey(BigInteger p) {
        List<BigInteger> primeList = getPrimeList(p);
        return primeList.get(random.nextInt(primeList.size()));
    }

    public BigInteger publicKey(BigInteger p, BigInteger g, BigInteger a) {
        return g.modPow(a, p);
    }

    public BigInteger secret(BigInteger p, BigInteger b, BigInteger a) {
        return b.modPow(a, p);
    }

    private List<BigInteger> getPrimeList(BigInteger max) {
        List<BigInteger> primes = new ArrayList<>();
        if (max.compareTo(BigInteger.TWO) <= 0) {
            return primes;
        }

        primes.add(BigInteger.TWO);
        for (BigInteger i = BigInteger.valueOf(3); i.compareTo(max) < 0; i = i.add(BigInteger.TWO)) {
            if (isPrime(i, primes)) {
                primes.add(i);
            }
        }
        return primes;
    }

    private boolean isPrime(BigInteger number, List<BigInteger> primes) {
        BigInteger sqrt = number.sqrt();
        for (BigInteger prime : primes) {
            if (prime.compareTo(sqrt) > 0) {
                break;
            }
            if (number.mod(prime).equals(BigInteger.ZERO)) {
                return false;
            }
        }
        return true;
    }
}