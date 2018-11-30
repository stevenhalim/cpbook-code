import java.util.*;

class Main { /* UVa 11450 - Wedding Shopping - Top Down */
  private static int M, C, K;
  private static int[][] price = new int[25][25]; // price[g (<= 20)][model (<= 20)]
  private static int[][] memo = new int[210][25]; // dp table memo[money (<= 200)][g (<= 20)]

  private static int shop(int money, int g) {
    if (money < 0)            return -1000000000; // fail, return a large negative number (1B)
    if (g == C)               return M - money; // we have bought last garment, done
    if (memo[money][g] != -1) return memo[money][g]; // this state has been visited before
    int ans = -1000000000;
    for (int model = 1; model <= price[g][0]; model++) // try all possible models
      ans = Math.max(ans, shop(money - price[g][model], g + 1));
    return memo[money][g] = ans; // assign ans to dp table + return it!
  }

  public static void main(String[] args) { // easy to code if you are already familiar with it
    Scanner sc = new Scanner(System.in);
    int i, j, TC, score;

    TC = sc.nextInt();
    while (TC-- > 0) {
      M = sc.nextInt(); C = sc.nextInt();
      for (i = 0; i < C; i++) {
        K = sc.nextInt();
        price[i][0] = K; // to simplify coding, we store K in price[i][0]
        for (j = 1; j <= K; j++)
          price[i][j] = sc.nextInt();
      }

      for (i = 0; i < 210; i++)
        for (j = 0; j < 25; j++)
          memo[i][j] = -1; // initialize DP memo table

      score = shop(M, 0); // start the top-down DP
      if (score < 0) System.out.printf("no solution\n");
      else           System.out.printf("%d\n", score);
    }
  }
}
