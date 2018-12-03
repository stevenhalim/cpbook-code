// Modular Fibonacci, 0.282s in Java, 0.019s in C++

import java.util.*;

class Main {
  static int i, n, m, MAX_N = 2;
  static long MOD;

  static long[][] matMul(long[][] a, long[][] b) {    // O(n^3 ~> 1) as n=2
    long[][] ans = new long[2][2]; int i, j, k;
    for (i = 0; i < MAX_N; i++)
      for (j = 0; j < MAX_N; j++)
        for (ans[i][j] = k = 0; k < MAX_N; k++) {
          ans[i][j] += (a[i][k] % MOD) * (b[k][j] % MOD);
          ans[i][j] %= MOD;               // modulo arithmetic is used here
        }
    return ans;
  }

  static long[][] matPow(long[][] base, int p) {   // O(n^3 log p ~> log p)
    long[][] ans = new long[MAX_N][MAX_N]; int i, j;
    for (i = 0; i < MAX_N; i++)
      for (j = 0; j < MAX_N; j++)
        ans[i][j] = (i == j ? 1 : 0);            // prepare identity matrix
    while (p > 0) { // iterative version of Divide & Conquer exponentiation
      if ((p & 1) == 1)           // check if p is odd (the last bit is on)
        ans = matMul(ans, base);                              // update ans
      base = matMul(base, base);                         // square the base
      p >>= 1;                                             // divide p by 2
    }
    return ans;
  }

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    while (sc.hasNext()) {
      n = sc.nextInt(); m = sc.nextInt();
      long[][] ans = new long[MAX_N][MAX_N];   // special Fibonaccci matrix
      ans[0][0] = 1;  ans[0][1] = 1;
      ans[1][0] = 1;  ans[1][1] = 0;
      for (MOD = 1, i = 0; i < m; i++)                     // set MOD = 2^m
        MOD *= 2;
      ans = matPow(ans, n);                                     // O(log n)
      System.out.println(ans[0][1]);                      // this if fib(n)
    }
  }
}
