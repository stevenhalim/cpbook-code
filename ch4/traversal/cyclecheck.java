import java.util.*;
import java.io.*;

public class cyclecheck {
  private static final int UNVISITED = 0;
  private static final int EXPLORED = 2;         // now we need three flags
  private static final int VISITED = 1;

  // these variables have to be global to be easily accessible by our recursion (other ways exist)
  private static ArrayList<ArrayList<IntegerPair>> AL;
  private static ArrayList<Integer> dfs_num;
  private static ArrayList<Integer> dfs_parent;  // back vs bidirectional

  private static void cycleCheck(int u) {        // check edge properties
    dfs_num.set(u, EXPLORED);                    // color u as EXPLORED
    for (IntegerPair v_w : AL.get(u)) {
      if (dfs_num.get(v_w.first()) == UNVISITED) { // EXPLORED->UNVISITED
        dfs_parent.set(v_w.first(), u);          // a tree edge u->v
        cycleCheck(v_w.first());
      }
      else if (dfs_num.get(v_w.first()) == EXPLORED) { // EXPLORED->EXPLORED
        if (v_w.first() == dfs_parent.get(u))
          System.out.printf(" Bidirectional Edge (%d, %d) - (%d, %d)\n", u, v_w.first(), v_w.first(), u);
        else
          System.out.printf("Back Edge (%d, %d) (Cycle)\n", u, v_w.first());
      }
      else if (dfs_num.get(v_w.first()) == VISITED) // EXPLORED->VISITED
        System.out.printf("  Forward/Cross Edge (%d, %d)\n", u, v_w.first());
    }
    dfs_num.set(u, VISITED);                     // color u as VISITED/DONE
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

    // Scanner sc = new Scanner(new File("dfs_cc_in.txt"));

    /*
    // Directed graph in Figure 4.9
    8
    1 1 0
    1 3 0
    1 1 0
    2 2 0 4 0
    1 5 0
    1 7 0
    1 4 0
    1 6 0
    */

    Scanner sc = new Scanner(new File("scc_in.txt"));

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

    System.out.printf("Graph Edges Property Check\n");
    dfs_num = new ArrayList<>(Collections.nCopies(V, UNVISITED));
    dfs_parent = new ArrayList<>(Collections.nCopies(V, -1));
    for (int u = 0; u < V; ++u)
      if (dfs_num.get(u) == UNVISITED)
        cycleCheck(u);
  }
}
