import java.util.*;

class Main { /* How do you add? */
  // top-down

  private static int N, K;
  private static int[][] memo = new int[110][110];

  private static int ways(int N, int K) {
    if (K == 1) // only can use 1 number to add up to N
      return 1; // the answer is definitely 1, that number itself
    else if (memo[N][K] != -1)
      return memo[N][K];

    // if K > 1, we can choose one number from [0..N] to be one of the number
    // and recursively compute the rest
    int total_ways = 0;
    for (int split = 0; split <= N; split++)
      total_ways = (total_ways + ways(N - split, K - 1)) % 1000000; // we just need the modulo 1M
    return memo[N][K] = total_ways; // memoize them
  }

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);

    for (int i = 0; i < 110; i++)
      for (int j = 0; j < 110; j++)
        memo[i][j] = -1;

    while (true) {
      N = sc.nextInt();
      K = sc.nextInt();
      if (N == 0 && K == 0)
        break;
      System.out.printf("%d\n", ways(N, K)); // some recursion formula + top down DP
    }
  }
}
