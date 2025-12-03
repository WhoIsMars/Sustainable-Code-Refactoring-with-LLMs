import java.math.BigInteger;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class DiffieHellman {

   private Random random = new Random();

   public BigInteger privateKey(BigInteger p) {
      BigInteger min = BigInteger.TWO;
      BigInteger max = p.subtract(BigInteger.ONE);
      BigInteger range = max.subtract(min).add(BigInteger.ONE);

      BigInteger candidate;
      do {
         candidate = new BigInteger(p.bitLength(), random);
      } while (candidate.compareTo(min) < 0 || candidate.compareTo(max) > 0 || !isPrime(candidate));

      return candidate;
   }

   public BigInteger publicKey(BigInteger p, BigInteger g, BigInteger a) {
      return g.modPow(a, p);
   }

   public BigInteger secret(BigInteger p, BigInteger b, BigInteger a) {
      return b.modPow(a, p);
   }

   private boolean isPrime(BigInteger n) {
      if (n.compareTo(BigInteger.ONE) <= 0) return false;
      if (n.compareTo(BigInteger.valueOf(3)) <= 0) return true;
      if (n.mod(BigInteger.TWO).equals(BigInteger.ZERO) || n.mod(BigInteger.valueOf(3)).equals(BigInteger.ZERO)) return false;

      for (BigInteger i = BigInteger.valueOf(5); i.multiply(i).compareTo(n) <= 0; i = i.add(BigInteger.valueOf(6))) {
         if (n.mod(i).equals(BigInteger.ZERO) || n.mod(i.add(BigInteger.TWO)).equals(BigInteger.ZERO))
            return false;
      }
      return true;
   }
}