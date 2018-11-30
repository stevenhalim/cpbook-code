import java.util.*;
import java.io.*;

public class ch4_05_dijkstra {
  public static final int INF = 1000000000;
  private static Vector< Vector< IntegerPair > > AdjList = new Vector< Vector< IntegerPair > >();
  
  public static void main(String[] args) throws Exception {
    int V, E, s, u, v, w;

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

    File f = new File("in_05.txt");
    Scanner sc = new Scanner(f);
    V = sc.nextInt();
    E = sc.nextInt();
    s = sc.nextInt();

    AdjList.clear();
    for (int i = 0; i < V; i++) {
      Vector< IntegerPair > Neighbor = 
        new Vector < IntegerPair >();
      AdjList.add(Neighbor); // add neighbor list to Adjacency List
    }

    for (int i = 0; i < E; i++) {
      u = sc.nextInt();
      v = sc.nextInt();
      w = sc.nextInt();
      AdjList.get(u).add(new IntegerPair (v, w)); // first time using weight
    }

    // Dijkstra routine
    Vector < Integer > dist = new Vector < Integer > ();
    dist.addAll(Collections.nCopies(V, INF)); dist.set(s, 0); // INF = 1*10^9 not MAX_INT to avoid overflow
    PriorityQueue < IntegerPair > pq = new PriorityQueue < IntegerPair >(1, 
      new Comparator< IntegerPair >() { // overriding the compare method 
        public int compare(IntegerPair i, IntegerPair j) {
          return i.first() - j.first();
        }
      }
    );
    pq.offer(new IntegerPair (0, s)); // sort based on increasing distance

    while (!pq.isEmpty()) { // main loop
      IntegerPair top = pq.poll(); // greedy: pick shortest unvisited vertex
      int d = top.first(); u = top.second();
      if (d > dist.get(u)) continue; // This check is important! We want to process vertex u only once but we can
      Iterator it = AdjList.get(u).iterator();
      while (it.hasNext()) { // all outgoing edges from u
        IntegerPair p = (IntegerPair) it.next();
        v = p.first();
        int weight_u_v = p.second();
        if (dist.get(u) + weight_u_v < dist.get(v)) { // if can relax      (note: Record SP spanning tree)
          dist.set(v, dist.get(u) + weight_u_v); // relax                  (here if needed. This is similar)
          pq.offer(new IntegerPair(dist.get(v), v)); //      (as printpath in BFS)
          // enqueue this neighbor regardless whether it is already in pq or not    
    } } }
  
    for (int i = 0; i < V; i++) // index + 1 for final answer
      System.out.printf("SSSP(%d, %d) = %d\n", s + 1, i + 1, dist.get(i));
  }
}
