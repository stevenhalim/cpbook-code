import java.io.*;
import java.util.*;

class Main { /* UVa 11065 - Gentlemen Agreement */
  private static final int MAXI = 62;

  private static long LSOne(long S) {
    return ((S) & -(S));
  }

  private static long[] AM = new long[MAXI];
  private static int V, numIS, MIS;

  private static void backtrack(int u, long mask, int depth) {
    if (mask == 0) {                             // all have been visited
      ++numIS;                                   // one more possible IS
      MIS = Math.max(MIS, depth);                // size of the set
    }
    else {
      long m = mask;
      while (m > 0) {
        long two_pow_v = LSOne(m);
        int v = (int)(Math.log(two_pow_v)/Math.log(2.0)); // v is not yet used
        m -= two_pow_v;
        if (v < u) continue;                     // do not double count
        backtrack(v+1, mask & ~AM[v], depth+1);  // use v + its neighbors
      }
    }
  }

  public static void main(String[] args) throws Exception {
    // This solution is nearly TLE without using BufferedReader and PrintWriter
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    int TC = Integer.parseInt(br.readLine());
    String[] tokens;
    while (TC-- > 0) {
      tokens = br.readLine().split(" ");
      V = Integer.parseInt(tokens[0]); int E = Integer.parseInt(tokens[1]);
      // compact AM for faster set operations
      for (int u = 0; u < V; ++u)
        AM[u] = (1L<<u);                         // u to itself
      while (E-- > 0) {
        tokens = br.readLine().split(" ");
        int a = Integer.parseInt(tokens[0]), b = Integer.parseInt(tokens[1]);
        AM[a] |= (1L<<b);
        AM[b] |= (1L<<a);
      }
      numIS = MIS = 0;
      backtrack(0, (1L<<V)-1, 0);                // backtracking + bitmask
      pw.println(numIS);
      pw.println(MIS);
    }
    pw.close();
  }
}
