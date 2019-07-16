import java.util.*;
import java.io.*;

public class bfs {
  private static final int INF = 1000000000;

  private static ArrayList<Integer> p = new ArrayList<>();

  private static void printPath(int u) {
    if (p.get(u) == -1) { System.out.printf("%d", u); return; }
    printPath(p.get(u));
    System.out.printf(" %d", u);
  }
  
  public static void main(String[] args) throws Exception {
    /*
    // Graph in Figure 4.3, format: list of unweighted edges
    // This example shows another form of reading graph input
    13 16
    0 1    1 2    2  3   0  4   1  5   2  6    3  7   5  6
    4 8    8 9    5 10   6 11   7 12   9 10   10 11  11 12
    */

    Scanner sc = new Scanner(new File("bfs_in.txt"));

    int V = sc.nextInt(), E = sc.nextInt();
    ArrayList<ArrayList<IntegerPair>> AL = new ArrayList<>();
    for (int u = 0; u < V; ++u) {
      ArrayList<IntegerPair> Neighbor = new ArrayList<>();
      AL.add(Neighbor);
    }
    while (E-- > 0) {
      int a = sc.nextInt(), b = sc.nextInt();
      AL.get(a).add(new IntegerPair(b, 0));
      AL.get(b).add(new IntegerPair(a, 0));
    }

    // as an example, we start from this source, see Figure 4.3
    int s = 5;

    // BFS routine inside void main(String[] args) -- we do not use recursion
    ArrayList<Integer> dist = new ArrayList<>(Collections.nCopies(V, INF)); dist.set(s, 0); // INF = 1e9 here
    Queue<Integer> q = new LinkedList<>(); q.offer(s);
    p.clear(); p.addAll(Collections.nCopies(V, -1)); // p is global

    int layer = -1;                              // for output printing
    Boolean isBipartite = true;                  // additional feature

    while (!q.isEmpty()) {
      int u = q.poll();
      if (dist.get(u) != layer) System.out.printf("\nLayer %d: ", dist.get(u));
      layer = dist.get(u);
      System.out.printf("visit %d, ", u);
      for (IntegerPair v_w : AL.get(u)) {
        int v = v_w.first();                     // w ignored
        if (dist.get(v) == INF) {
          dist.set(v, dist.get(u)+1);            // dist[v] != INF now
          p.set(v, u);                           // parent of v is u
          q.offer(v);                            // for next iteration
        }
        else if ((dist.get(v)%2) == (dist.get(u)%2)) // same parity
          isBipartite = false;
      }
    }

    System.out.printf("\nShortest path: ");
    printPath(7); System.out.printf("\n");
    System.out.printf("isBipartite? %d\n", isBipartite ? 1 : 0);
  }
}
