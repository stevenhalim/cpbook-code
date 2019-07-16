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
    for (int u = 0; u < V; ++u) {
      ArrayList<IntegerPair> Neighbor = new ArrayList<>();
      AL.add(Neighbor);
    }
    while (E-- > 0) {
      int u = sc.nextInt(), v = sc.nextInt(), w = sc.nextInt();
      AL.get(u).add(new IntegerPair(v, w));
    }
    
  // Bellman Ford's routine, basically = relax all E edges V-1 times
    ArrayList<Integer> dist = new ArrayList<>(Collections.nCopies(V, INF)); dist.set(s, 0); // INF = 1e9 here
    for (int i = 0; i < V-1; ++i) {              // total O(V*E)
      Boolean modified = false;                  // optimization
      for (int u = 0; u < V; ++u)                // these two loops = O(E)
        if (dist.get(u) != INF)                  // important check
          for (IntegerPair v_w : AL.get(u)) {
            int v = v_w.first(), w = v_w.second();
            if (dist.get(u)+w >= dist.get(v)) continue; // not improving, skip
            dist.set(v, dist.get(u)+w);          // relax operation
            modified = true;                     // optimization
          }
      if (!modified) break;
    }

    Boolean hasNegativeCycle = false;
    for (int u = 0; u < V; ++u)                  // one more pass to check
      if (dist.get(u) != INF)
        for (IntegerPair v_w: AL.get(u)) {
          int v = v_w.first(), w = v_w.second();
          if (dist.get(v) > dist.get(u)+w)       // should be false
          hasNegativeCycle = true;               // if true => -ve cycle
        }
    System.out.printf("Negative Cycle Exist? %s\n", hasNegativeCycle ? "Yes" : "No");

    if (!hasNegativeCycle)
      for (int u = 0; u < V; ++u)
        System.out.printf("SSSP(%d, %d) = %d\n", s, u, dist.get(u));
  }
}
