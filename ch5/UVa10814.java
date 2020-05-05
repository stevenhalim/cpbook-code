// 0.212s in Java

import java.util.Scanner;
import java.math.BigInteger;

class Main {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    int N = sc.nextInt();
    while (N-- > 0) {                            // we have to use > 0
      BigInteger p = sc.nextBigInteger();
      String ch = sc.next();                     // ignore this char
      BigInteger q = sc.nextBigInteger();
      BigInteger gcd_pq = p.gcd(q);              // wow :)
      System.out.println(p.divide(gcd_pq) + " / " + q.divide(gcd_pq));
    }
  }
}
