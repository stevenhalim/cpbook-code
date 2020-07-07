import java.io.*;
import java.util.*;

class Main { /* UVa 01238 - Free Parentheses */
  private static int[] num = new int[35], sign = new int[35];
  private static int cnt;
  private static int[][][] memo = new int[35][35][6500];
  private static TreeSet<Integer> S;

  private static void dp(int open, int n, int value) {
    if (memo[open][n][value+3200] != -1) return;
    if (n == cnt-1) {
      S.add(value);
      return;
    }
    int nval = sign[n+1] * num[n+1] * (open%2 == 0 ? 1 : -1);
    if (open > 0) dp(open-1, n+1, value+nval);
    if (sign[n+1] == -1) dp(open+1, n+1, value+nval);
    dp(open, n+1, value+nval);
    memo[open][n][value+3200] = 0;
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
      cnt = 1;
      S = new TreeSet<>();
      while (st.hasMoreTokens()) {
        sign[cnt] = (st.nextToken().equals("-") ? -1 : 1);
        num[cnt] = Integer.parseInt(st.nextToken());
        ++cnt;
      }
      for (int i = 0; i < 35; ++i)
        for (int j = 0; j < 35; ++j)
          for (int k = 0; k < 6500; ++k)
            memo[i][j][k] = -1;
      dp(0, 0, num[0]);
      pw.println(S.size());
    }
    pw.close();
  }
}
