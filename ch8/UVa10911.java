import java.io.*;
import java.util.*;

class Main {                                     // UVa default class name
  static int N, target;                          // max N = 8
  static double[][] dist = new double[20][20];
  static double[] memo = new double[1<<16];      // 1<<16 = 2^16

  static double matching(int mask) {             // DP state = mask
    // we initialize `memo' with -1.0 in the main function
    if (memo[mask] > -0.5) return memo[mask];    // this has been computed
    if (mask == target) return 0;                // all have been matched
    double ans = 1e9;                            // init with a large value
    int p1, p2;
    for (p1 = 0; p1 < 2*N; ++p1)
      if ((mask & (1<<p1)) == 0)
        break;                                   // find the first off bit
    for (p2 = p1+1; p2 < 2*N; ++p2)              // then, try to match p1
      if ((mask & (1<<p2)) == 0)                 // with other off bit p2
        ans = Math.min(ans,                      // pick the minimum
                       dist[p1][p2] + matching(mask | (1<<p1) | (1<<p2)));
    return memo[mask] = ans;                     // store result in a table
  }

  public static void main(String[] args) throws Exception {
    BufferedReader br = 
      new BufferedReader(new InputStreamReader(System.in));
    PrintWriter pw = new PrintWriter(System.out);
    int caseNo = 0;
    int[] x = new int[20], y = new int[20];
    while (true) {
      N = Integer.parseInt(br.readLine());
      if (N == 0) break;
      for (int i = 0; i < 2*N; ++i) {
        String[] token = br.readLine().split(" ");
        x[i] = Integer.parseInt(token[1]);
        y[i] = Integer.parseInt(token[2]);
      }
      for (int i = 0; i < 2*N-1; ++i)            // build distance table
        for (int j = i+1; j < 2*N; ++j)          // use `hypot' function
          dist[i][j] = dist[j][i] = Math.hypot(x[i]-x[j], y[i]-y[j]);
      // DP to solve min weighted perfect matching on small general graph
      for (int i = 0; i < (1<<(2*N)); ++i)
        memo[i] = -1.0;
      target = (1<<(2*N)) - 1;
      pw.printf("Case %d: %.2f\n", ++caseNo, matching(0));
    }
    pw.close();
  }
}
