// Bicoloring

import java.util.*;

class Main {
  private static final int INF = 1000000000;

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    while (true) {
      int n = sc.nextInt();
      if (n == 0) break;
      ArrayList<ArrayList<Integer>> AL = new ArrayList<>();
      for (int i = 0; i < n; ++i)
        AL.add(new ArrayList<>());
      int l = sc.nextInt();
      while (l-- > 0) {
        int a = sc.nextInt(), b = sc.nextInt();
        AL.get(a).add(b);
        AL.get(b).add(a);                        // bidirectional
      }
      int s = 0;
      Queue<Integer> q = new LinkedList<>(); q.add(s);
      ArrayList<Integer> color = new ArrayList<>(Collections.nCopies(n, INF)); color.set(s, 0);
      Boolean isBipartite = true;                // add a Boolean flag
      while (!q.isEmpty() && isBipartite) {      // as with original BFS
        int u = q.poll();
        for (Integer v : AL.get(u)) {
          if (color.get(v) == INF) {             // don't record distances
            color.set(v, 1-color.get(u));        // just record two colors
            q.add(v);
          }
          else if (color.get(v) == color.get(u)) { // u & v have same color
            isBipartite = false;                 // a coloring conflict :(
            break;                               // optional speedup
          }
        }
      }
      System.out.printf("%sBICOLORABLE.\n", (isBipartite ? "" : "NOT "));
    }
  }
}
