import static java.math.BigInteger.ONE;
import static java.math.BigInteger.TWO;
import static java.math.BigInteger.ZERO;

import java.math.BigInteger;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class DiffieHellman {

   private final Random random = new Random();

   public BigInteger privateKey(BigInteger p) {
      List<BigInteger> primes = getPrimeList(p);
      return primes.get(random.nextInt(primes.size()));
   }

   public BigInteger publicKey(BigInteger p, BigInteger g, BigInteger a) {
      return g.modPow(a, p);
   }

   public BigInteger secret(BigInteger p, BigInteger b, BigInteger a) {
      return b.modPow(a, p);
   }

   private List<BigInteger> getPrimeList(BigInteger max) {
      List<BigInteger> primes = new ArrayList<>();
      for (BigInteger current = TWO; current.compareTo(max) < 0; current = current.add(ONE)) {
         if (isPrime(current, primes)) {
            primes.add(current);
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