import java.util.*;
import java.io.*;

public class dijkstra {
  public static final int INF = 1000000000;
  
  public static void main(String[] args) throws Exception {
    /*
    // Graph in Figure 4.17
    5 7 2
    2 1 2
    2 3 7
    2 0 6
    1 3 3
    1 4 6
    3 4 5
    0 4 1
    */

    Scanner sc = new Scanner(new File("dijkstra_in.txt"));

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

    ArrayList<Integer> dist = new ArrayList<>(Collections.nCopies(V, INF)); dist.set(s, 0); // INF = 1e9 here

    // Original Dijkstra's algorithm
    /*
    TreeSet<IntegerPair> pq = new TreeSet<>();   // balanced BST version
    for (int u = 0; u < V; ++u)                  // dist[u] = INF
      pq.add(new IntegerPair(dist.get(u), u));   // but dist[s] = 0

    // sort the pairs by non-decreasing distance from s
    while (!pq.isEmpty()) {                      // main loop
      IntegerPair top = pq.pollFirst();
      int u = top.second();                      // shortest unvisited u
      for (IntegerPair v_w : AL.get(u)) {        // all edges from u
        int v = v_w.first(), w = v_w.second();
        if (dist.get(u)+w >= dist.get(v)) continue; // not improving, skip
        pq.remove(new IntegerPair(dist.get(v), v)); // erase old pair
        dist.set(v, dist.get(u)+w);              // relax operation
        pq.add(new IntegerPair(dist.get(v), v)); // enqueue better pair
      }
    }
    */

    // (Modified) Dijkstra's algorithm
    PriorityQueue<IntegerPair> pq = new PriorityQueue<>(); pq.offer(new IntegerPair(0, s));

    // sort the pairs by non-decreasing distance from s
    while (!pq.isEmpty()) {                      // main loop
      IntegerPair top = pq.poll();
      int d = top.first(), u = top.second();     // shortest unvisited u
      if (d > dist.get(u)) continue;             // a very important check
      for (IntegerPair v_w : AL.get(u)) {        // all edges from u
        int v = v_w.first(), w = v_w.second();
        if (dist.get(u)+w >= dist.get(v)) continue; // not improving, skip
        dist.set(v, dist.get(u)+w);              // relax operation
        pq.offer(new IntegerPair(dist.get(v), v)); // enqueue better pair
      }
    }
  
    for (int u = 0; u < V; ++u)
      System.out.printf("SSSP(%d, %d) = %d\n", s, u, dist.get(u));
  }
}
