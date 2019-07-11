import java.util.*;
import java.io.*;

public class dfs_cc {
  private static final int UNVISITED = 0;        // we only need these two
  private static final int VISITED = 1;

  // these variables have to be global to be easily accessible by our recursion (other ways exist)
  private static ArrayList<ArrayList<IntegerPair>> AL;
  private static ArrayList<Integer> dfs_num;
  private static ArrayList<Integer> ts;

  private static void dfs(int u) {               // normal usage
    System.out.printf(" %d", u);                 // this vertex is visited
    dfs_num.set(u, VISITED);                     // mark u as visited
    for (IntegerPair v_w : AL.get(u))            // w ignored
      if (dfs_num.get(v_w.first()) == UNVISITED) // to avoid cycle
        dfs(v_w.first());                        // recursively visits v
  }

  public static void main(String[] args) throws Exception {
    /*
    // Undirected Graph in Figure 4.1
    9
    1 1 0
    3 0 0 2 0 3 0
    2 1 0 3 0
    3 1 0 2 0 4 0
    1 3 0
    0
    2 7 0 8 0
    1 6 0
    1 6 0
    */

    Scanner sc = new Scanner(new File("dfs_cc_in.txt"));

    int V = sc.nextInt();
    AL = new ArrayList<>();
    for (int u = 0; u < V; ++u) {
      AL.add(new ArrayList<>());                 // store blank vector first
      int k = sc.nextInt();
      while (k-- > 0) {
        int v = sc.nextInt(), w = sc.nextInt();
        AL.get(u).add(new IntegerPair(v, w));
      }
    }

    System.out.printf("Standard DFS Demo (the input graph must be UNDIRECTED)\n");
    dfs_num = new ArrayList<>(Collections.nCopies(V, UNVISITED));
    int numCC = 0;
    for (int u = 0; u < V; ++u)                  // for each u in [0..V-1]
      if (dfs_num.get(u) == UNVISITED) {         // if that u is unvisited
        System.out.printf("CC %d:", ++numCC);
        dfs(u);
        System.out.printf("\n");
      }
    System.out.printf("There are %d connected components\n", numCC);
  }
}
