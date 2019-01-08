// ACORN, UVa 1231, LA 4106, 0.???s in Java (submission error?), 0.344s in C++

import java.util.*;

class UVa01231 {
  public static void main(String[] args) {
    int i, j, c, t, h, f, a, n;
    int[][] acorn = new int[2010][2010];
    int[] dp = new int[2010];
    Scanner sc = new Scanner(System.in);

    c = sc.nextInt();
    while (c-- > 0) {
      t = sc.nextInt(); h = sc.nextInt(); f = sc.nextInt();
      for (i = 0; i < 2010; i++)
        for (j = 0; j < 2010; j++)
          acorn[i][j] = 0;
      for (i = 0; i < t; i++) {
        a = sc.nextInt();
        for (j = 0; j < a; j++) {
          n = sc.nextInt();
          acorn[i][n]++; // there is an acorn here
        }
      }

      for (int tree = 0; tree < t; tree++) // initialization
        dp[h] = Math.max(dp[h], acorn[tree][h]);
      for (int height = h - 1; height >= 0; height--)
        for (int tree = 0; tree < t; tree++) {
          acorn[tree][height] +=
            Math.max(acorn[tree][height + 1], // from this tree, +1 above
            ((height + f <= h) ? dp[height + f] : 0)); // best from tree at height + f
          dp[height] = Math.max(dp[height], acorn[tree][height]); // update this too
        }
      System.out.printf("%d\n", dp[0]); // solution will be here
    }
    // ignore the last number 0
  }
}
