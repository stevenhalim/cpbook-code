import java.util.*;
import java.io.*;

public class prim {
  static ArrayList<ArrayList<IntegerPair>> AL = new ArrayList<>();
  static ArrayList<Boolean> taken = new ArrayList<>(); // global boolean flag to avoid cycle
  static PriorityQueue<IntegerPair> pq = new PriorityQueue<>(); // priority queue to help choose shorter edges

  static void process(int u) { //  we do not need to use -ve sign to reverse the sort order
    taken.set(u, true);
    for (IntegerPair v_w : AL.get(u))
      if (!taken.get(v_w.first()))
        pq.offer(new IntegerPair(v_w.second(), v_w.first()));
  }

  public static void main(String[] args) throws Exception {
    /*
    // Graph in Figure 4.10 left, format: list of weighted edges
    // This example shows another form of reading graph input
    5 7
    0 1 4
    0 2 4
    0 3 6
    0 4 6
    1 2 2
    2 3 8
    3 4 9
    */

    File f = new File("mst_in.txt");
    Scanner sc = new Scanner(f);

// inside int main() --- assume the graph is stored in AL, pq is empty
    int V = sc.nextInt(), E = sc.nextInt();
    AL.clear();
    for (int i = 0; i < V; ++i) {
      ArrayList<IntegerPair> Neighbor = new ArrayList<>();
      AL.add(Neighbor);                          // a blank ArrayList
    }
  
    // sort by edge weight O(E log E)
    // PQ default: sort descending. Trick: use <(negative) weight(i, j), <i, j> >
    for (int i = 0; i < E; ++i) {
      int u = sc.nextInt(), v = sc.nextInt(), w = sc.nextInt();
      AL.get(u).add(new IntegerPair(v, w));
      AL.get(v).add(new IntegerPair(u, w));
    }

    int mst_cost = 0, num_taken = 0;             // no edge has been taken
    for (int i = 0; i < V; ++i)
      taken.add(false);                          // no vertex has been taken
    process(0);                                  // take & process vertex 0
    while (!pq.isEmpty()) {                      // up to O(E)
      IntegerPair front = pq.peek(); pq.poll();
      int u = front.second(), w = front.first(); // no need to negate id/weight
      if (taken.get(u)) continue;                // already taken, skipped
      mst_cost += w;                             // add w of this edge
      process(u);                                // take+process vertex u
      ++num_taken;                               // 1 more edge is taken
      if (num_taken == V-1) break;               // optimization
    }
    System.out.printf("MST cost = %d (Prim's)\n", mst_cost);
  }
}
