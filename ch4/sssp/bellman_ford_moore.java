import java.util.*;
import java.io.*;

class spfa {
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

    // Graph in Figure 4.19, negative cycle exists, SPFA will be trapped in an infinite loop/produces WA (stop only when overflow happens)
    6 6 0
    0 1 99
    0 5 -99
    1 2 15
    2 3 0
    3 1 -42
    3 4 2
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

    // SPFA from source S
    ArrayList<Integer> dist = new ArrayList<>(Collections.nCopies(V, INF)); dist.set(s, 0); // INF = 1e9 here
    Queue<Integer> q = new LinkedList<>(); q.offer(s); // like BFS queue
    Vector<Boolean> in_queue = new Vector<>(Collections.nCopies(V, false)); in_queue.set(s, true); // unique to SPFA

    while (!q.isEmpty()) {
      int u = q.poll(); in_queue.set(u, false);  // pop from queue
      for (IntegerPair v_w : AL.get(u)) {
        int v = v_w.first(), w = v_w.second();
        if (dist.get(u)+w >= dist.get(v)) continue; // not improving, skip
        dist.set(v, dist.get(u)+w);              // relax operation
        if (!in_queue.get(v)) {                  // add to the queue
          q.offer(v);                            // only if v is not
          in_queue.set(v, true);                 // already in the queue
        }
      }
    }

    for (int u = 0; u < V; ++u)
      System.out.printf("SSSP(%d, %d) = %d\n", s, u, dist.get(u));
  }
}
