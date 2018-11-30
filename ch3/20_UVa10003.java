import java.util.*;

class Main { /* Cutting Sticks, 1.762s in Java, 0.302s in C++ */
  // Top-Down DP

  private static int[] arr = new int[55];
  private static int[][] memo = new int[55][55];

  private static int cut(int left, int right) {
    if (left + 1 == right)       return 0;
    if (memo[left][right] != -1) return memo[left][right];

    int ans = 2000000000;
    for (int i = left + 1; i < right; i++)
      ans = Math.min(ans, cut(left, i) + cut(i, right) + (arr[right] - arr[left]));
    return memo[left][right] = ans;
  }

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    int i, j, l, n;

    while (true) {
      l = sc.nextInt();
      if (l == 0)
        break;

      arr[0] = 0;
      n = sc.nextInt();
      for (i = 1; i <= n; i++)
        arr[i] = sc.nextInt();
      arr[n + 1] = l;

      for (i = 0; i < 55; i++)
        for (j = 0; j < 55; j++)
          memo[i][j] = -1;

      // start with left = 0 and right = n + 1
      System.out.printf("The minimum cutting is %d.\n", cut(0, n + 1));
    }
  }
}
