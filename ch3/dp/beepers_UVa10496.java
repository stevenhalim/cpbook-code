import java.util.*;

class beepers_UVa10496 { // Collecting Beepers
  // DP TSP

  private static int i, j, n;
  private static int[][] dist = new int[11][11], memo = new int[11][1 << 11]; // Karel + max 10 beepers

  private static int dp(int pos, int bitmask) { // bitmask stores the visited coordinates
    if (bitmask == (1 << (n + 1)) - 1)
      return dist[pos][0]; // return trip to close the loop
    if (memo[pos][bitmask] != -1)
      return memo[pos][bitmask];

    int ans = 2000000000;
    for (int nxt = 0; nxt <= n; nxt++) // O(n) here
      if (nxt != pos && (bitmask & (1 << nxt)) == 0) // if coordinate nxt is not visited yet
        ans = Math.min(ans, dist[pos][nxt] + dp(nxt, bitmask | (1 << nxt)));
    return memo[pos][bitmask] = ans;
  }

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    int TC = sc.nextInt();
    while (TC-- > 0) {
      int xsize = sc.nextInt(), ysize = sc.nextInt(); // these two values are not used
      int[] x = new int[11], y = new int[11];
      x[0] = sc.nextInt(); y[0] = sc.nextInt();
      n = sc.nextInt();
      for (i = 1; i <= n; ++i) { // karel's position is at index 0
        x[i] = sc.nextInt();
        y[i] = sc.nextInt();
      }

      for (i = 0; i <= n; ++i) // build distance table
        for (j = i; j <= n; ++j)
          dist[i][j] = dist[j][i] = Math.abs(x[i]-x[j]) + Math.abs(y[i]-y[j]); // Manhattan distance

      for (i = 0; i < 11; ++i)
        for (j = 0; j < (1 << 11); ++j)
          memo[i][j] = -1;

      System.out.printf("%d\n", dp(0, 1));       // DP-TSP
      // System.out.printf("The shortest path has length %d\n", dp(0, 1)); // DP-TSP
    }
  }
}
