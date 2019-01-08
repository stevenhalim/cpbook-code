// 0.345s in Java

import java.util.Scanner;
import java.math.BigInteger;

class Main {                                   // UVa 10551 - Basic Remains
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    while (true) {
      int b = sc.nextInt();
      if (b == 0) break;                    // special class's constructor!
      BigInteger p = new BigInteger(sc.next(), b);  // the second parameter
      BigInteger m = new BigInteger(sc.next(), b);           // is the base
      System.out.println((p.mod(m)).toString(b)); // can output in any base
} } }
