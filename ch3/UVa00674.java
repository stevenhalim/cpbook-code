import java.util.*;
import java.io.*;

class UVa00674 { /* Coin Change, 1.492s in Java, 0.038s in C++ */
  // O(NV) DP solution

  // N and coinValue are fixed for this problem, max V is 7489
  private static int N = 5, V;
  private static int[] coinValue = new int[] {1, 5, 10, 25, 50};
  private static int[][] memo = new int[6][7500];

  private static int ways(int type, int value) {
    if (value == 0)              return 1;
    if (value < 0 || type == N)  return 0;
    if (memo[type][value] != -1) return memo[type][value];
    return memo[type][value] = ways(type + 1, value) + ways(type, value - coinValue[type]);
  }

  public static void main(String[] args) throws Exception {
    // This solution is TLE without using BufferedReader and PrintWriter
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter pr = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

    for (int i = 0; i < 6; i++)
      for (int j = 0; j < 7500; j++)
        memo[i][j] = -1; // we only need to initialize this once

    while (true) {
      String line = br.readLine();
      if (line == null) break;
      V = Integer.parseInt(line);
      pr.printf("%d\n", ways(0, V));
    }

    pr.close(); // do not forget to do this
  }
}
