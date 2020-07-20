import java.io.*;
import java.util.*;

class Main { /* UVa 10243 - Fire! Fire!! Fire!!! */
  private static int[][] memo = new int[1010][2];
  private static ArrayList<ArrayList<Integer>> AL; // undirected version
  private static ArrayList<ArrayList<Integer>> Children; // directed version
  private static ArrayList<Integer> vis;

  private static void dfs(int u) {
    vis.set(u, 1);
    for (Integer v : AL.get(u))
      if (vis.get(v) == 0) {
        Children.get(u).add(v);                  // now u<->v becomes u->v
        dfs(v);
      }
  }

  private static int MVC(int u, int flag) {      // get |MVC| on Tree
    if (memo[u][flag] != -1) return memo[u][flag]; // top down DP
    int ans = 0;
    if (Children.get(u).size() == 0)             // u is a leaf
      ans = flag;                                // 1/0 = taken/not
    else if (flag == 0) {                        // if u is not taken,
      ans = 0;                                   // we must take
      for (Integer v : Children.get(u))          // all its children
        ans += MVC(v, 1);
    }
    else if (flag == 1) {                        // if u is taken,
      ans = 1;                                   // we take the minimum
      for (Integer v : Children.get(u))          // between taking or
        ans += Math.min(MVC(v, 1), MVC(v, 0));   // not taking its children
    }
    return ans;
  }

  public static void main(String[] args) throws Exception {
    // This solution is TLE without using BufferedReader and PrintWriter
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    String[] tokens;
    while (true) {
      int N = Integer.parseInt(br.readLine());
      if (N == 0) break;
      AL = new ArrayList<>();
      Children = new ArrayList<>();
      for (int u = 0; u < N; ++u) { // Adj List of each vertex, 0-based
        AL.add(new ArrayList<>());
        Children.add(new ArrayList<>());
        tokens = br.readLine().split(" ");
        int ni = Integer.parseInt(tokens[0]);
        for (int i = 1; i <= ni; ++i) {
          int v = Integer.parseInt(tokens[i])-1; // 0-based indexing
          AL.get(u).add(v);
        }
      }
      if (N == 1) { // special case
        pw.println(1); // still need 1 fire exit
        continue;
      }
      vis = new ArrayList<>(Collections.nCopies(N, 0));
      dfs(0); // root the tree at vertex 0
      for (int i = 0; i < N; ++i)
        for (int j = 0; j < 2; ++j)
          memo[i][j] = -1;
      pw.println(Math.min(MVC(0, 1), MVC(0, 0)));
    }
    pw.close();
  }
}
