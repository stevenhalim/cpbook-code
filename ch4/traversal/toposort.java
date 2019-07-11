import java.util.*;
import java.io.*;

public class toposort {
  private static final int UNVISITED = 0;        // we only need these two
  private static final int VISITED = 1;

  // these variables have to be global to be easily accessible by our recursion (other ways exist)
  private static ArrayList<ArrayList<IntegerPair>> AL;
  private static ArrayList<Integer> dfs_num;
  private static ArrayList<Integer> ts;

  private static void toposort(int u) {
    dfs_num.set(u, VISITED);
    for (IntegerPair v_w : AL.get(u))
      if (dfs_num.get(v_w.first()) == UNVISITED)
        toposort(v_w.first());
    ts.add(u);                                   // this is the only change
  }

  public static void main(String[] args) throws Exception {
    /*
    // Example of a Directed Acyclic Graph in Figure 4.4 (for toposort)
    8
    2 1 0 2 0
    2 2 0 3 0
    2 3 0 5 0
    1 4 0
    0
    0
    0
    1 6 0
    */

    Scanner sc = new Scanner(new File("toposort_in.txt"));

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

    // make sure that the given graph is DAG
    System.out.printf("Topological Sort (the input graph must be DAG)\n");
    dfs_num = new ArrayList<>(Collections.nCopies(V, UNVISITED)); // global variable
    ts = new ArrayList<>();                      // global variable
    for (int u = 0; u < V; ++u)
      if (dfs_num.get(u) == UNVISITED)
        toposort(u);
    // reverse ts or simply read the content of ts backwards
    for (int i = ts.size()-1; i >= 0; --i)
      System.out.printf(" %d", ts.get(i));
    System.out.printf("\n");
  }
}
