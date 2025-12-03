import static java.math.BigInteger.ONE;
import static java.math.BigInteger.TWO;
import static java.math.BigInteger.ZERO;

import java.math.BigInteger;
import java.security.SecureRandom;
import java.util.ArrayList;
import java.util.List;

public class DiffieHellman {

   private static final SecureRandom random = new SecureRandom();
   private static final BigInteger THREE = BigInteger.valueOf(3);
   private List<BigInteger> cachedPrimes;
   private BigInteger cachedMax;

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
      if (cachedPrimes != null && max.equals(cachedMax)) {
         return cachedPrimes;
      }
      
      cachedMax = max;
      cachedPrimes = sieveOfEratosthenes(max);
      return cachedPrimes;
   }

   private List<BigInteger> sieveOfEratosthenes(BigInteger max) {
      if (max.compareTo(TWO) <= 0) {
         return new ArrayList<>();
      }
      
      int limit = max.intValue();
      boolean[] isPrime = new boolean[limit];
      
      for (int i = 2; i < limit; i++) {
         isPrime[i] = true;
      }
      
      for (int i = 2; i * i < limit; i++) {
         if (isPrime[i]) {
            for (int j = i * i; j < limit; j += i) {
               isPrime[j] = false;
            }
         }
      }
      
      List<BigInteger> primes = new ArrayList<>();
      for (int i = 2; i < limit; i++) {
         if (isPrime[i]) {
            primes.add(BigInteger.valueOf(i));
         }
      }
      
      return primes;
   }
}