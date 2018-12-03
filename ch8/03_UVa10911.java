import java.util.*;

class Main { /* UVa 10911 - Forming Quiz Teams, 0.462s in Java, 0.032s in C++ */
  private static int N, target;
  private static double dist[][] = new double[20][], memo[] = new double[65536]; // this is 2^16, max N = 8

  private static double matching(int bitmask) {         // DP state = bitmask
                         // we initialize `memo' with -1 in the main function
    if (memo[bitmask] > -0.5)          // this state has been computed before
      return memo[bitmask];                   // simply lookup the memo table
    if (bitmask == target)                // all students are already matched
      return memo[bitmask] = 0;                              // the cost is 0

    double ans = 2000000000.0;               // initialize with a large value
    int p1, p2;
    for (p1 = 0; p1 < 2 * N; p1++)
      if ((bitmask & (1 << p1)) == 0)
        break;                              // find the first bit that is off
    for (p2 = p1 + 1; p2 < 2 * N; p2++)              // then, try to match p1
      if ((bitmask & (1 << p2)) == 0) // with another bit p2 that is also off
        ans = Math.min(ans,                               // pick the minimum
                  dist[p1][p2] + matching(bitmask | (1 << p1) | (1 << p2)));

    return memo[bitmask] = ans;    // store result in a memo table and return
  }

  public static void main(String[] args) {
    int i, j, caseNo = 1;
    int[] x = new int[20], y = new int[20];

    Scanner sc = new Scanner(System.in);
    while (true) {
      N = sc.nextInt();
      if (N == 0)
        break;

      for (i = 0; i < 2 * N; i++) {
        String name = sc.next(); // dummy
        x[i] = sc.nextInt();
        y[i] = sc.nextInt();
      }

      for (i = 0; i < 2 * N - 1; i++) {
        dist[i] = new double[20];
        for (j = 0; j < 2 * N; j++)
          dist[i][j] = Math.hypot(x[i] - x[j], y[i] - y[j]);
      }

      // use DP to solve min weighted perfect matching on small general graph
      for (i = 0; i < 65536; i++)
        memo[i] = -1.0;
      target = (1 << (2 * N)) - 1;
      System.out.printf("Case %d: %.2f\n", caseNo++, matching(0));
    }
  }
}
