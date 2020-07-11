import java.io.*;
import java.util.*;

class Main { /* UVa 01238 - Free Parentheses */
  private static final int MAX_N = 35;
  private static final int OFFSET = 3000;
  private static int[] num = new int[MAX_N], sign = new int[MAX_N];
  private static int N;
  private static Boolean[][][] visited = new Boolean[MAX_N][MAX_N][6010];
  private static HashSet<Integer> S;

  private static void dp(int idx, int open, int val) { // OFFSET = 3000
    if (visited[idx][open][val+OFFSET])          // has been reached before
      return;                                    // +3000 offset to make
                                                 // indices in [100..6000]
    visited[idx][open][val+OFFSET] = true;       // set this to true
    if (idx == N) {                              // last number
      S.add(val);                                // val is one
      return;                                    // of expression result
    }
    int nval = val + num[idx] * sign[idx] * ((open%2 == 0) ? 1 : -1);
    if (sign[idx] == -1)                         // 1: put open bracket
      dp(idx+1, open+1, nval);                   //    only if sign is -
    if (open > 0)                                // 2: put close bracket
      dp(idx+1, open-1, nval);                   //    if we have >1 opens
    dp(idx+1, open, nval);                       // 3: do nothing
  }

  public static void main(String[] args) throws Exception {
    // This solution is nearly TLE without using BufferedReader and PrintWriter
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    while (true) {
      String line = br.readLine();
      if (line == null) break;
      StringTokenizer st = new StringTokenizer(line);
      sign[0] = 1;
      num[0] = Integer.parseInt(st.nextToken());
      N = 1;
      S = new HashSet<>();
      while (st.hasMoreTokens()) {
        sign[N] = (st.nextToken().equals("-") ? -1 : 1);
        num[N] = Integer.parseInt(st.nextToken());
        ++N;
      }
      for (int i = 0; i < MAX_N; ++i)
        for (int j = 0; j < MAX_N; ++j)
          for (int k = 0; k < 6010; ++k)
            visited[i][j][k] = false;
      dp(0, 0, num[0]);
      pw.println(S.size());
    }
    pw.close();
  }
}
