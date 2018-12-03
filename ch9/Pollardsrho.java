import java.math.*;
import java.security.SecureRandom;

class Pollardsrho {
  private static BigInteger TWO = BigInteger.valueOf(2);
  private final static SecureRandom random = new SecureRandom();

  private static BigInteger f(BigInteger x, BigInteger b, BigInteger n) {
    return x.multiply(x).mod(n).add(b).mod(n);     // x = (x^2 % n + b) % n
  }

  private static BigInteger rho(BigInteger n) {
    if (n.mod(TWO).compareTo(BigInteger.ZERO) == 0) return TWO;  // special
    BigInteger b = new BigInteger(n.bitLength(), random);  // rand for luck
    BigInteger x = new BigInteger(n.bitLength(), random);
    BigInteger y = x;                                    // initially y = x
    while (true) {
      x = f(x, b, n);                                           // x = f(x)
      y = f(f(y, b, n), b, n);                               // y = f(f(y))
      BigInteger d = x.subtract(y).gcd(n);                 // d = (x-y) % n
      if (d.compareTo(BigInteger.ONE) != 0)                    // if d != 1
        return d;          // d is one of the divisor of composite number n
  } }

  public static void pollard_rho(BigInteger n) {
    if (n.compareTo(BigInteger.ONE) == 0) return;    // special case, n = 1
    if (n.isProbablePrime(10)) {
      System.out.println(n); return;  // n is a prime, the only factor is n
    }
    BigInteger divisor = rho(n);   // n is a composite number, can be split
    pollard_rho(divisor);                     // recursive check to divisor
    pollard_rho(n.divide(divisor));                        // and n/divisor
  }

  public static void main(String[] args) {
    BigInteger n = new BigInteger("124590589650069032140693");       // Big
    pollard_rho(n);       // factorize n to 7 x 124418296927 x 143054969437
  }
}
