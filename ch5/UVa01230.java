// 0.080s in Java

import java.util.Scanner;
import java.math.BigInteger;

class Main {                                     // UVa 01230 (LA 4104)
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    int c = sc.nextInt();
    while (c-- > 0) {
      BigInteger x, y, n;
      x = BigInteger.valueOf(sc.nextInt());      // valueOf converts
      y = BigInteger.valueOf(sc.nextInt());      // simple integer
      n = BigInteger.valueOf(sc.nextInt());      // into BigInteger
      System.out.println(x.modPow(y, n));        // it's in the library!
    }
  }
}
