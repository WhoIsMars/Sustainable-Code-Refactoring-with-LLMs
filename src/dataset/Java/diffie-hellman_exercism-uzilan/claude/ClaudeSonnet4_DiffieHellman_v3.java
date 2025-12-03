import static java.math.BigInteger.ONE;
import static java.math.BigInteger.TWO;
import static java.math.BigInteger.ZERO;

import java.math.BigInteger;
import java.security.SecureRandom;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.function.BiFunction;
import java.util.function.BinaryOperator;

public class DiffieHellman {

   private static final SecureRandom random = new SecureRandom();
   private static final BigInteger THREE = BigInteger.valueOf(3);
   private static final BigInteger FIVE = BigInteger.valueOf(5);

   public BigInteger privateKey(BigInteger p) {
      if (p.compareTo(TWO) <= 0) {
         return TWO;
      }
      
      BigInteger min = TWO;
      BigInteger max = p.subtract(ONE);
      BigInteger range = max.subtract(min);
      
      BigInteger result;
      do {
         result = new BigInteger(range.bitLength(), random).add(min);
      } while (result.compareTo(max) >= 0);
      
      return result;
   }

   public BigInteger publicKey(BigInteger p, BigInteger g, BigInteger a) {
      return g.modPow(a, p);
   }

   public BigInteger secret(BigInteger p, BigInteger b, BigInteger a) {
      return b.modPow(a, p);
   }

   private List<BigInteger> getPrimeList(BigInteger max) {
      List<BigInteger> primes = new ArrayList<>();
      
      if (max.compareTo(TWO) > 0) {
         primes.add(TWO);
      }
      if (max.compareTo(THREE) > 0) {
         primes.add(THREE);
      }
      
      BigInteger current = FIVE;
      while (current.compareTo(max) < 0) {
         if (isPrimeOptimized(current, primes)) {
            primes.add(current);
         }
         current = current.add(TWO);
      }
      
      return primes;
   }

   private final BiFunction<ArrayList<BigInteger>, BigInteger, ArrayList<BigInteger>> accumulator =
      (acc, current) -> {
         if (isPrime(current, acc)) {
            acc.add(current);
         }
         return acc;
      };

   private final BinaryOperator<ArrayList<BigInteger>> combiner =
      (accumulator, bigIntegers) -> {
         accumulator.addAll(bigIntegers);
         return accumulator;
      };

   private boolean isPrime(BigInteger bigInteger, List<BigInteger> list) {
      return list.stream().noneMatch(current -> bigInteger.mod(current).equals(ZERO));
   }

   private boolean isPrimeOptimized(BigInteger n, List<BigInteger> primes) {
      BigInteger sqrt = sqrt(n);
      for (BigInteger prime : primes) {
         if (prime.compareTo(sqrt) > 0) {
            break;
         }
         if (n.mod(prime).equals(ZERO)) {
            return false;
         }
      }
      return true;
   }

   private BigInteger sqrt(BigInteger n) {
      if (n.equals(ZERO)) {
         return ZERO;
      }
      
      BigInteger x = n;
      BigInteger y = n.add(ONE).divide(TWO);
      
      while (y.compareTo(x) < 0) {
         x = y;
         y = x.add(n.divide(x)).divide(TWO);
      }
      
      return x;
   }
}