import java.math.BigInteger;
import java.security.SecureRandom;
import java.util.ArrayList;
import java.util.List;

public class DiffieHellman {

   private final SecureRandom secureRandom = new SecureRandom();

   public BigInteger privateKey(BigInteger p) {
      return BigInteger.TWO.add(new BigInteger(p.bitLength() - 2, secureRandom)).mod(p.subtract(BigInteger.TWO));
   }

   public BigInteger publicKey(BigInteger p, BigInteger g, BigInteger a) {
      return g.modPow(a, p);
   }

   public BigInteger secret(BigInteger p, BigInteger b, BigInteger a) {
      return b.modPow(a, p);
   }

   private List<BigInteger> getPrimeList(BigInteger max) {
      List<BigInteger> primes = new ArrayList<>();
      for (BigInteger i = BigInteger.TWO; i.compareTo(max) < 0; i = i.add(BigInteger.ONE)) {
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
         if (candidate.mod(prime).equals(BigInteger.ZERO)) return false;
      }
      return true;
   }
}