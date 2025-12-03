import static java.math.BigInteger.ONE;
import static java.math.BigInteger.TWO;
import static java.math.BigInteger.ZERO;

import java.math.BigInteger;
import java.util.Random;
import java.security.SecureRandom;

public class DiffieHellman {

   private static final SecureRandom random = new SecureRandom();

   public BigInteger privateKey(BigInteger p) {
      // Generate a random private key in range [2, p-2]
      BigInteger min = TWO;
      BigInteger max = p.subtract(TWO);
      
      if (max.compareTo(min) <= 0) {
         return min;
      }
      
      BigInteger range = max.subtract(min).add(ONE);
      BigInteger result;
      do {
         result = new BigInteger(range.bitLength(), random);
      } while (result.compareTo(range) >= 0);
      
      return result.add(min);
   }

   public BigInteger publicKey(BigInteger p, BigInteger g, BigInteger a) {
      return g.modPow(a, p);
   }

   public BigInteger secret(BigInteger p, BigInteger b, BigInteger a) {
      return b.modPow(a, p);
   }
}