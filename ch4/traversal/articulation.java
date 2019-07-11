import java.util.*;
import java.io.*;

public class articulation {
  private static final int UNVISITED = 0;        // we only need this

  // these variables have to be global to be easily accessible by our recursion (other ways exist)
  private static ArrayList<ArrayList<IntegerPair>> AL;
  private static ArrayList<Integer> dfs_num, dfs_low, dfs_parent, articulation_vertex;
  private static int dfsNumberCounter, dfsRoot, rootChildren;

  private static void articulationPointAndBridge(int u) {
    dfs_low.set(u, dfsNumberCounter);
    dfs_num.set(u, dfsNumberCounter++); // dfs_low[u] <= dfs_num[u]
    for (IntegerPair v_w : AL.get(u)) {
      if (dfs_num.get(v_w.first()) == UNVISITED) { // a tree edge
        dfs_parent.set(v_w.first(), u);
        if (u == dfsRoot) ++rootChildren;        // special case, root

        articulationPointAndBridge(v_w.first());

        if (dfs_low.get(v_w.first()) >= dfs_num.get(u)) // for articulation point
          articulation_vertex.set(u, 1); // store this information first
        if (dfs_low.get(v_w.first()) > dfs_num.get(u)) // for bridge
          System.out.printf(" Edge (%d, %d) is a bridge\n", u, v_w.first());
        dfs_low.set(u, Math.min(dfs_low.get(u), dfs_low.get(v_w.first()))); // update dfs_low[u]
      }
      else if (v_w.first() != dfs_parent.get(u)) // a back edge and not direct cycle
        dfs_low.set(u, Math.min(dfs_low.get(u), dfs_num.get(v_w.first()))); // update dfs_low[u]
    }
  }

  public static void main(String[] args) throws Exception {
    /*
    // Left graph in Figure 4.6/4.7/4.8
    6
    1 1 0
    3 0 0 2 0 4 0
    1 1 0
    1 4 0
    3 1 0 3 0 5 0
    1 4 0

    // Right graph in Figure 4.6/4.7/4.8
    6
    1 1 0
    5 0 0 2 0 3 0 4 0 5 0
    1 1 0
    1 1 0
    2 1 0 5 0
    2 1 0 4 0
    */

    Scanner sc = new Scanner(new File("articulation_in.txt"));

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

    System.out.printf("Articulation Points & Bridges (the input graph must be UNDIRECTED)\n");
    dfs_num = new ArrayList<>(Collections.nCopies(V, UNVISITED)); // global variable
    dfs_low = new ArrayList<>(Collections.nCopies(V, 0));
    dfs_parent = new ArrayList<>(Collections.nCopies(V, -1));
    articulation_vertex = new ArrayList<>(Collections.nCopies(V, 0));
    dfsNumberCounter = 0;
    System.out.printf("Bridges:\n");
    for (int u = 0; u < V; ++u)
      if (dfs_num.get(u) == UNVISITED) {
        dfsRoot = u; rootChildren = 0;
        articulationPointAndBridge(u);
        articulation_vertex.set(dfsRoot, (rootChildren > 1) ? 1 : 0); // special case
      }

    System.out.printf("Articulation Points:\n");
    for (int u = 0; u < V; ++u)
      if (articulation_vertex.get(u) == 1)
        System.out.printf(" Vertex %d\n", u);
  }
}
