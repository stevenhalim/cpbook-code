// 0.345s in Java

import java.util.Scanner;
import java.math.BigInteger;

class Main {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);         // a few test cases
    while (true) {
      int b = sc.nextInt(); if (b == 0) break;
      BigInteger p = new BigInteger(sc.next(), b); // 2nd parameter
      BigInteger m = new BigInteger(sc.next(), b); // is the base
      System.out.println((p.mod(m)).toString(b)); // print in base b
    }
  }
}
