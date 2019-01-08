import java.util.*;
import java.io.*;

public class bellman_ford {
  public static final int INF = 1000000000;
	  
  public static void main(String[] args) throws Exception {
    /*
    // Graph in Figure 4.18, has negative weight, but no negative cycle
    5 5 0
    0 1 1
    0 2 10
    1 3 2
    2 3 -10
    3 4 3

    // Graph in Figure 4.19, negative cycle exists
    3 3 0
    0 1 1000
    1 2 15
    2 1 -42
    */

    Scanner sc = new Scanner(new File("bellman_ford_in.txt"));

    int V = sc.nextInt(), E = sc.nextInt(), s = sc.nextInt();
    ArrayList<ArrayList<IntegerPair>> AL = new ArrayList<>();
    for (int i = 0; i < V; i++) {
      ArrayList<IntegerPair> Neighbor = new ArrayList<>();
      AL.add(Neighbor); // add neighbor list to Adjacency List
    }

    for (int i = 0; i < E; i++) {
      int u = sc.nextInt(), v = sc.nextInt(), w = sc.nextInt();
      AL.get(u).add(new IntegerPair(v, w)); // first time using weight
    }
    
    // Bellman Ford's routine
    ArrayList<Integer> dist = new ArrayList<>(Collections.nCopies(V, INF)); dist.set(s, 0);
    for (int i = 0; i < V-1; i++) // relax all E edges V-1 times, O(V)
      for (int u = 0; u < V; u++) // these two loops = O(E)
        if (dist.get(u) != INF) // important: do not propagate if dist[u] == INF
          for (IntegerPair v_w : AL.get(u))   // we can record SP spanning here if needed
            dist.set(v_w.first(), 
              Math.min(dist.get(v_w.first()), dist.get(u)+v_w.second()));

    Boolean hasNegativeCycle = false;
    for (int u = 0; u < V; u++) if (dist.get(u) != INF) // one more pass to check
      for (IntegerPair v_w: AL.get(u))
        if (dist.get(v_w.first()) > dist.get(u)+v_w.second()) // should be false, but if possible
          hasNegativeCycle = true;            // then negative cycle exists!
    System.out.printf("Negative Cycle Exist? %s\n", hasNegativeCycle ? "Yes" : "No");

    if (!hasNegativeCycle)
      for (int i = 0; i < V; i++)
        System.out.printf("SSSP(%d, %d) = %d\n", s, i, dist.get(i));
  }
}
