import java.util.*;

class Main { /* SuperSale */
  // 0-1 Knapsack DP (Top-Down) - faster as not all states are visited

  private static final int MAX_N = 1010;
  private static final int MAX_W = 40;
  private static int N, MW;
  private static int[] V = new int[MAX_N], W = new int[MAX_N];
  private static int[][] memo = new int[MAX_N][MAX_W];

  private static int value(int id, int w) {
    if (id == N || w == 0) return 0;
    if (memo[id][w] != -1) return memo[id][w];
    if (W[id] > w)         return memo[id][w] = value(id + 1, w);
    return memo[id][w] = Math.max(value(id + 1, w), V[id] + value(id + 1, w - W[id]));
  }

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    int i, j, T, G, ans;

    T = sc.nextInt();
    while (T-- > 0) {
      for (i = 0; i < MAX_N; i++)
        for (j = 0; j < MAX_W; j++)
          memo[i][j] = -1;

      N = sc.nextInt();
      for (i = 0; i < N; i++) {
        V[i] = sc.nextInt();
        W[i] = sc.nextInt();
      }

      ans = 0;
      G = sc.nextInt();
      while (G-- > 0) {
        MW = sc.nextInt();
        ans += value(0, MW);
      }

      System.out.printf("%d\n", ans);
    }
  }
}
