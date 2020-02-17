import java.util.*;

class UVa10130 { /* SuperSale */
  // 0-1 Knapsack DP (Top-Down) - faster as not all states are visited

  private static final int MAX_N = 1010;
  private static final int MAX_W = 40;
  private static int N;
  private static int[] V = new int[MAX_N], W = new int[MAX_N];
  private static int[][] memo = new int[MAX_N][MAX_W];

  private static int dp(int id, int remW) {
    if ((id == N) || (remW == 0)) return 0;
    if (memo[id][remW] != -1) return memo[id][remW];
    if (W[id] > remW) return memo[id][remW] = dp(id+1, remW);
    return memo[id][remW] = Math.max(dp(id+1, remW),
                                     V[id]+dp(id+1, remW-W[id]));
  }

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);

    int T = sc.nextInt();
    while (T-- > 0) {
      for (int i = 0; i < MAX_N; ++i)
        for (int j = 0; j < MAX_W; ++j)
          memo[i][j] = -1;

      N = sc.nextInt();
      for (int i = 0; i < N; ++i) {
        V[i] = sc.nextInt();
        W[i] = sc.nextInt();
      }

      int ans = 0;
      int G = sc.nextInt();
      while (G-- > 0) {
        int MW = sc.nextInt();
        ans += dp(0, MW);
      }

      System.out.printf("%d\n", ans);
    }
  }
}
