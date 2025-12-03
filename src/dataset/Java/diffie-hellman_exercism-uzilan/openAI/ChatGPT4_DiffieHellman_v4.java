import static java.math.BigInteger.ONE;
import static java.math.BigInteger.TWO;
import static java.math.BigInteger.ZERO;

import java.math.BigInteger;
import java.security.SecureRandom;
import java.util.ArrayList;
import java.util.List;

public class DiffieHellman {

    private final SecureRandom random = new SecureRandom();

    public BigInteger privateKey(BigInteger p) {
        return new BigInteger(p.bitLength() - 1, random).add(TWO).mod(p.subtract(TWO)).add(TWO);
    }

    public BigInteger publicKey(BigInteger p, BigInteger g, BigInteger a) {
        return g.modPow(a, p);
    }

    public BigInteger secret(BigInteger p, BigInteger b, BigInteger a) {
        return b.modPow(a, p);
    }

    private List<BigInteger> getPrimeList(BigInteger max) {
        List<BigInteger> primes = new ArrayList<>();
        for (BigInteger i = TWO; i.compareTo(max) < 0; i = i.add(ONE)) {
            if (isPrime(i, primes)) {
                primes.add(i);
            }
        }
        return primes;
    }

    private boolean isPrime(BigInteger candidate, List<BigInteger> primes) {
        BigInteger sqrt = candidate.sqrt();
        for (BigInteger prime : primes) {
            if (prime.compareTo(sqrt) > 0) break;
            if (candidate.mod(prime).equals(ZERO)) return false;
        }
        return true;
    }
}